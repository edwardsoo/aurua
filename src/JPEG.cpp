/************************************************************
*	APRON TUTORIALS PRESENTED BY MORROWLAND					*
*************************************************************
*	Author					: Ronny Andr� Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
*	Version					: English (UK)					*
************************************************************/
#if defined(__APPLE_CC__)
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
#elif defined(WIN32)
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdint.h>
#endif

#include"jpeg.h"

// Modified by Edward Soo for UBC CPSC 314 project

/////////////////////////////////////////////////////////////////////////////////////////////////
//										JPEG TEXTURE LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////



void JPEG_Texture(UINT textureArray[], LPSTR strFileName, int ID)
{
	if(!strFileName)	return;
	
	tImageJPG *pBitMap = Load_JPEG(strFileName);
	
	if(pBitMap == NULL)	exit(0);
	
	glGenTextures(1, &textureArray[ID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitMap->sizeX, pBitMap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitMap->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	
	
	if (pBitMap)									
	{
		if (pBitMap->data)					
		{
			free(pBitMap->data);			
		}
		free(pBitMap);
	}
}





tImageJPG *Load_JPEG(const char *strfilename)
{
	struct jpeg_decompress_struct cInfo;
	tImageJPG *pImgData = NULL;
	FILE *pFile;
	
	if((pFile = fopen(strfilename, "rb")) == NULL) 
	{
		printf("Error loading jpg file.\n");
		return NULL;
	}
	
	jpeg_error_mgr jerr;

	cInfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cInfo);

	jpeg_stdio_src(&cInfo, pFile);
	
	pImgData = (tImageJPG*)malloc(sizeof(tImageJPG));

	Decompress_JPEG(&cInfo, pImgData);

	jpeg_destroy_decompress(&cInfo);
	
	fclose(pFile);
	
	return pImgData;
}


void Decompress_JPEG(jpeg_decompress_struct* cInfo, tImageJPG *pImgData)
{
	jpeg_read_header(cInfo, TRUE);
	
	jpeg_start_decompress(cInfo);
	
	pImgData->rowSpan = cInfo->image_width * cInfo->num_components;
	pImgData->sizeX   = cInfo->image_width;
	pImgData->sizeY   = cInfo->image_height;
	
	pImgData->data = new unsigned char[pImgData->rowSpan * pImgData->sizeY];
	
	unsigned char** rowPtr = new unsigned char*[pImgData->sizeY];
	for (int i = 0; i < pImgData->sizeY; i++)
		rowPtr[i] = &(pImgData->data[i*pImgData->rowSpan]);
	
	int rowsRead = cInfo->output_height-1;
	while (cInfo->output_scanline < cInfo->output_height) 
	{
		rowsRead -= jpeg_read_scanlines(cInfo, &rowPtr[rowsRead], cInfo->output_height - rowsRead);
	}
	delete [] rowPtr;
	
	jpeg_finish_decompress(cInfo);
}




//Ronny Andr� Reierstad
//www.morrowland.com
//apron@morrowland.com
