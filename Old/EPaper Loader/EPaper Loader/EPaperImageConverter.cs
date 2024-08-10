using Microsoft.VisualBasic.FileIO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SixLabors.ImageSharp;
using SixLabors.ImageSharp.ColorSpaces;
using SixLabors.ImageSharp.PixelFormats;

namespace EPaper_Loader
{
    class EPaperImageConverter
    {
        private char[,]? stream = null;
        private int width = 0;
        private int height = 0;
        private int colors = 0;
        private bool imgValid = false;

        public EPaperImageConverter()
        {

        }

        public bool LoadImage(string img)
        {
            try
            {
                SixLabors.ImageSharp.Image<Rgb24> image = SixLabors.ImageSharp.Image.Load<Rgb24>(img);

                width = image.Width;
                height = image.Height;

                //Black and White
                colors = 2;

                stream = new char[width, height];

                Rgb24 red = new Rgb24(255, 0, 0);
                Rgb24 white = new Rgb24(255, 255, 255);
                Rgb24 black = new Rgb24(0, 0, 0);
                Rgb24 yellow = new Rgb24(255, 255, 0);

                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        Rgb24 pixel = image[x, y];
                        if (pixel == white)
                        {
                            //White
                            stream[x, y] = 'W';
                        }
                        else if (pixel == black)
                        {
                            //Black
                            stream[x, y] = 'B';
                        }
                        else if (pixel == red)
                        {
                            //Red
                            stream[x, y] = 'R';
                            if (colors != 4)
                            {
                                colors = 3;
                            }
                        }
                        else if (pixel == yellow)
                        {
                            //Yellow
                            stream[x, y] = 'Y';
                            colors = 4;
                        }
                        else
                        {
                            //Invalid
                            stream[x, y] = '?';
                            colors = -1;
                            imgValid = false;
                        }
                    }
                }

                imgValid = true;
                image.Dispose();
            }
            catch
            {
                return false;
            }

            return true;
        }

        public int getWidth()
        {
            return width;
        }

        public int getHeight()
        {
            return height;
        }

        public int getColors()
        {
            return colors;
        }

        public char getPixel(int x, int y)
        {
            if (stream == null)
            {
                return '\0';
            }
            return stream[x, y];
        }

        public bool isValid()
        {
            return imgValid;
        }
    }
}
