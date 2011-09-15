/**
* Project: VSXu: Realtime visual programming language, music/audio visualizer, animation tool and much much more.
*
* @see The Lesser GNU Public License (GPL)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the Lesser GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the Lesser GNU General Public License
* for more details.
*
* You should have received a copy of the Lesser GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef __FTGLBitmapFont__
#define __FTGLBitmapFont__

#include "FTFont.h"
#include "FTGL.h"


class FTGlyph;

/**
 * FTGLBitmapFont is a specialisation of the FTFont class for handling
 * Bitmap fonts
 *
 * @see     FTFont
 */
class FTGL_EXPORT FTGLBitmapFont : public FTFont
{
    public:
        /**
         * Open and read a font file. Sets Error flag.
         *
         * @param fontname  font file name.
         */
        FTGLBitmapFont( const char* fontname);

        /**
         * Open and read a font from a buffer in memory. Sets Error flag.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTGLBitmapFont( const unsigned char *pBufferBytes, size_t bufferSizeInBytes);

        /**
         * Destructor
         */
        ~FTGLBitmapFont();
        
        /**
         * Renders a string of characters
         * 
         * @param string    'C' style string to be output.   
         */
        void Render( const char* string);

        /**
         * Renders a string of characters
         * 
         * @param string    'C' style wide string to be output.  
         */
        void Render( const wchar_t* string);

        // attributes
        
    private:
        /**
         * Construct a FTBitmapGlyph.
         *
         * @param g The glyph index NOT the char code.
         * @return  An FTBitmapGlyph or <code>null</code> on failure.
         */
        inline virtual FTGlyph* MakeGlyph( unsigned int g);
                
};
#endif  //  __FTGLBitmapFont__
