//------------------------------------------------------------------------------
//  n2converterapp.cc
//  (C) 2008 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "n2converterapp.h"
#include "io/textwriter.h"
#include "toolkitutil/binarymodelwriter.h"

namespace Toolkit
{
using namespace IO;
using namespace Util;
using namespace Math;
using namespace ToolkitUtil;

//------------------------------------------------------------------------------
/**
*/
N2ConverterApp::N2ConverterApp() :
    logResources(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
N2ConverterApp::ParseCmdLineArgs()
{
    if (ToolkitApp::ParseCmdLineArgs())
    {
        this->n2Converter.SetForceFlag(this->args.GetBoolFlag("-force"));
        this->n2Converter.SetBinaryFlag(!this->args.GetBoolFlag("-xml"));
        this->n2Converter.SetVerbose(this->args.GetBoolFlag("-verbose"));
        this->category = this->args.GetString("-cat", "");
        this->filename = this->args.GetString("-file", "");
        this->logResources = this->args.GetBoolFlag("-logresources");
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
/**
*/
bool
N2ConverterApp::SetupProjectInfo()
{
    if (ToolkitApp::SetupProjectInfo())
    {
        this->n2Converter.SetPlatform(this->platform);
        this->n2Converter.SetSrcDir(this->projectInfo.GetAttr("N2ConverterSrcDir"));
        this->n2Converter.SetDstDir(this->projectInfo.GetAttr("N2ConverterDstDir"));
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
N2ConverterApp::ShowHelp()
{
    n_printf("Nebula3 N2 model file converter.\n"
             "(C) Radon Labs GmbH 2008.\n"
             "-help         -- display this help\n"
             "-platform     -- select platform (win32, xbox360, wii, ps3)\n"
             "-waitforkey   -- wait for key when complete\n"
             "-force        -- force export (don't check time stamps)\n"             
             "-cat          -- select specific category\n"
             "-file         -- select specific file (also needs -cat)\n"
             "-xml          -- output XML files (default is binary)\n"
             "-logresources -- create resource log file in proj directory\n"
             "-verbose      -- display status info\n");
}

void WriteBlankTerrainTile()
{
	// write model
	IoServer* ioServer = IoServer::Instance();
	Ptr<Stream> stream = ioServer->CreateStream("mdl:editor/terraintile_0_0.n3");
	Ptr<BinaryModelWriter> writer = BinaryModelWriter::Create();
	writer->SetStream(stream);
	if (writer->Open())
	{
		writer->BeginModel("Models::Model", FourCC('MODL'), "editor/terraintile");

		String chunkName;

		for (int z = 0; z < 16; ++z)
		{
			for (int x = 0; x < 16; ++x)
			{
				chunkName.Format("chunk_%d_%d", x, z);
				writer->BeginModelNode("Terrain::TerrainChunkNode", FourCC('TECN'), chunkName);

				// node type
				writer->BeginTag("ModelNodeType", FourCC('MNTP'));
				writer->WriteString("Terrain1");
				writer->EndTag();

				// shader
				writer->BeginTag("Shader", FourCC('SHDR'));
				writer->WriteString("shd:terrain");
				writer->EndTag();

				// diffuse texture
				writer->BeginTag("ShaderTexture", FourCC('STXT'));
				writer->WriteString("DiffMap0");
				writer->WriteString("tex:system/white");
				writer->EndTag();

				// texture number
				writer->BeginTag("TextureNumber", FourCC('TCTN'));
				writer->WriteInt(1);				
				writer->EndTag();

				// base y
				writer->BeginTag("BaseY", FourCC('TCBY'));
				writer->WriteFloat(0.0);
				writer->EndTag();

				// height map
				writer->BeginTag("Height", FourCC('TCHT'));
				for (int i = 0; i < 145; ++i)
				{
					writer->WriteFloat(0.0);
				}
				writer->EndTag();

				// normal
				writer->BeginTag("Normal", FourCC('TCNL'));
				for (int i = 0; i < 145; ++i)
				{
					writer->WriteFloat(0.0);
					writer->WriteFloat(1.0);
					writer->WriteFloat(0.0);
				}
				writer->EndTag();

				// alpha map

				// shadow map

				writer->EndModelNode();
			}
		}

		writer->EndModel();
	}
}

struct ChunkData 
{
	float ybase;
	float height[145];
	float normal[145 * 3];
	unsigned char blendMap[64*64*4];
	int nTextures;
	int texIndex[4];
};

void Adt2N3(String srcFile, String dstFile)
{
	IoServer* ioServer = IoServer::Instance();
	Ptr<Stream> srcStream = ioServer->CreateStream(srcFile);
	Ptr<BinaryReader> reader = BinaryReader::Create();
	reader->SetStream(srcStream);

	if (reader->Open())
	{
		int size;
		reader->ReadInt();
		reader->ReadInt();
		size = reader->ReadInt();

		Array<String> textures;
		char* buffer = new char[size];
		reader->ReadRawData(buffer, size);

		// texture list
		char* p = buffer;
		while (p < (buffer + size)) 
		{
			String texpath(p);
			p += strlen(p) + 1;

			texpath = texpath.ExtractFileName();
			texpath.TrimRight(".blp");
			textures.Append("Tileset/" + texpath + "_s.tga");
		}

		delete[] buffer;

		// write model
		srcFile.TrimRight(".adt");
		Array<String> tokens = srcFile.Tokenize("_");
		int xTile = 0;//tokens[1].AsInt();
		int zTile = 0;//64 - tokens[2].AsInt();

		Ptr<Stream> dstStream = ioServer->CreateStream(dstFile);
		Ptr<BinaryModelWriter> writer = BinaryModelWriter::Create();
		writer->SetStream(dstStream);

		if (writer->Open())
		{
			int x, z;
			String str;
			ChunkData chunk;

#define TILESIZE (533.33333f)
#define CHUNKSIZE ((TILESIZE) / 16.0f)

			writer->BeginModel("Models::Model", FourCC('MODL'), "terraintile");
			writer->BeginModelNode("Models::TransformNode", FourCC('TRFN'), "tilenode");
			// tile base coordinates
			writer->BeginTag("Position", FourCC('POSI'));
			writer->WriteFloat4(float4(xTile*TILESIZE, 0.0, zTile*TILESIZE, 1.0));
			writer->EndTag();

			for (z = 0; z < 16; ++z)
			{
				for (x = 0; x < 16; ++x)
				{
					reader->ReadRawData(&chunk, sizeof(ChunkData));

					str.Format("chunk_%d_%d", x, z);
					writer->BeginModelNode("Terrain::TerrainNode", FourCC('TERN'), str);
					
					// base info
					writer->BeginTag("BaseInfo", FourCC('TEBI'));
					writer->WriteUChar(xTile);
					writer->WriteUChar(zTile);
					writer->WriteUChar(x);
					writer->WriteUChar(z);
					writer->EndTag();

					// chunk base coordinates
					writer->BeginTag("Position", FourCC('POSI'));
					writer->WriteFloat4(float4(x*CHUNKSIZE, chunk.ybase, z*CHUNKSIZE, 1.0));
					writer->EndTag();

					// node type
					writer->BeginTag("ModelNodeType", FourCC('MNTP'));
					writer->WriteString("Terrain" + String::FromInt(chunk.nTextures));
					writer->EndTag();

					// shader
					writer->BeginTag("Shader", FourCC('SHDR'));
					writer->WriteString("shd:terrain");
					writer->EndTag();

					// diffuse texture
					for (int i = 0; i < chunk.nTextures; ++i)
					{
						writer->BeginTag("ShaderTexture", FourCC('STXT'));
						writer->WriteString("DiffMap" + String::FromInt(i));
						writer->WriteString("tex:" + textures[chunk.texIndex[i]]);
						writer->EndTag();
					}

					// texture number
					writer->BeginTag("TextureNumber", FourCC('TETN'));
					writer->WriteInt(chunk.nTextures);				
					writer->EndTag();

					// height map
					writer->BeginTag("Height", FourCC('TEHT'));
					for (int i = 0; i < 145; ++i)
					{
						writer->WriteFloat(chunk.height[i]);
					}
					writer->EndTag();

					// normal
					writer->BeginTag("Normal", FourCC('TENL'));
					for (int i = 0; i < 145; ++i)
					{
						writer->WriteFloat(chunk.normal[i*3 + 0]);
						writer->WriteFloat(chunk.normal[i*3 + 1]);
						writer->WriteFloat(chunk.normal[i*3 + 2]);
					}
					writer->EndTag();

					// blend map
					writer->BeginTag("blendmap", FourCC('TEBM'));
					for (int i = 0; i < 64*64; ++i)
					{
						writer->WriteUChar(chunk.blendMap[i*4 + 1]);
						writer->WriteUChar(chunk.blendMap[i*4 + 2]);
						writer->WriteUChar(chunk.blendMap[i*4 + 3]);
					}
					writer->EndTag();

					// shadow map
					writer->BeginTag("shadowmap", FourCC('TESM'));
					for (int i = 0; i < 64*64; ++i)
					{
						writer->WriteUChar(chunk.blendMap[i*4 + 0]);
					}
					writer->EndTag();

					writer->EndModelNode();
				}
			}

			writer->EndModelNode();
			writer->EndModel();
		}
	}
}

//------------------------------------------------------------------------------
/**
*/
void
N2ConverterApp::Run()
{
	{
		//WriteBlankTerrainTile();
		Adt2N3("D:\\wow\\World\\HillsbradPast_29_25.adt", "mdl:editor/HillsbradPast_0_0.n3");
		return;
	}

    // parse command line args
    if (!this->ParseCmdLineArgs())
    {
        return;
    }

    // setup the project info object
    if (!this->SetupProjectInfo())
    {
        return;
    }

    // perform conversion
    this->n2Converter.Setup();
    bool result = true;
    if (this->category.IsValid())
    {
        if (this->filename.IsValid())
        {
            result = this->n2Converter.ConvertFile(this->logger, this->category, this->filename);
        }
        else
        {
            result = this->n2Converter.ConvertCategory(this->logger, this->category);
        }
    }
    else
    {
        result = this->n2Converter.ConvertAll(this->logger);
    }
    
    // log resources?
    if (this->logResources)
    {
        Ptr<Stream> stream = IoServer::Instance()->CreateStream("proj:n2conv_resourcelog.txt");
        Ptr<TextWriter> writer = TextWriter::Create();
        writer->SetStream(stream);
        if (writer->Open())
        {
            writer->WriteLines(this->n2Converter.GetUsedResources());
            writer->Close();
        }
    }
    this->n2Converter.Discard();
}

} // namespace Toolkit