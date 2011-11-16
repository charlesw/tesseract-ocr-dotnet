A tesseract-ocr .NET wrapper based on tesseractdotnet.

This project can be considered an (unofficial) fork off the tesseract-ocr 
project that adds a .NET wrapper using C++/CLI. It is based off the excellent 
work done by the tesseractocrdotnet team.

Code License: [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)  
Site Content License (Documentation etc): [Creative Commons Attribution 3.0 Unported License](license" href="http://creativecommons.org/licenses/by/3.0/)

## Example

    using System;
    using System.Collections.Generic;
    using System.Text;
    using System.IO;
    using System.Drawing;
    using OCR.TesseractWrapper;

    namespace tesseractconsole
    {
        public class Program
        {
            const string TessractData = @".\tessdata\";

            public static void Main(string[] args)
            {
                const string language = "eng";
                string imageFile = args[0];

                TesseractProcessor processor = new TesseractProcessor();

                using (var bmp = Bitmap.FromFile(imageFile) as Bitmap) {
                    var success = processor.Init(TessractData, language, (int)eOcrEngineMode.OEM_DEFAULT);
                    if (!success) {
                        Console.WriteLine("Failed to initialize tesseract.");
                    } else {
                        string text = processor.Recognize(bmp);
                        Console.WriteLine("Text:");
                        Console.WriteLine("*****************************");
                        Console.WriteLine(text);
                        Console.WriteLine("*****************************");
                    }
                }

                Console.WriteLine("Press any key to exit.");
                Console.ReadKey();
            }
        }
    }



