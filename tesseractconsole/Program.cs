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
		const string TessractData = @"..\..\..\..\tessdata\";

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