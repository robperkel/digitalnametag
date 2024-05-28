using System;
using System.Drawing;
using System.Windows;

namespace EPaper_Loader;

public partial class ImagePreview : ContentPage
{
	private byte[] textData;

	public ImagePreview()
	{
		InitializeComponent();
    }

    private void ContentPage_NavigatedTo(object sender, NavigatedToEventArgs e)
    {

    }
    private async void OpenButton_Clicked(object sender, EventArgs e)
    {
		PreviewImage.IsVisible = false;
		ImageTable.IsVisible = false;
        try
		{
            var result = await FilePicker.Default.PickAsync();
			
			if (result != null)
			{
				PreviewImage.Source = ImageSource.FromFile(result.FullPath);
				if (AppShell.EPaperLoadImage(result.FullPath))
				{
					//Show Data and Image
					ImageSizeText.Detail = AppShell.EPaperGetImageSize();
					ColorText.Detail = AppShell.EPaperGetColorMode();

                    PreviewImage.IsVisible = true;
                    ImageTable.IsVisible = true;

                }
            }
        }
		catch
		{
			//Error or no file
		}
    }
}