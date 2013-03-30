#ifndef JPEG_H
#define JPEG_H

#include "jpeglib.h"

// Modified by Edward Soo for UBC CPSC 314 project

tImageJPG *Load_JPEG(const char *strfilename);

void Decompress_JPEG(jpeg_decompress_struct* cInfo, tImageJPG *pImgData);

void JPEG_Texture(UINT textureArray[], LPSTR strFileName, int ID);

#endif



// www.morrowland.com
// apron@morrowland.com
