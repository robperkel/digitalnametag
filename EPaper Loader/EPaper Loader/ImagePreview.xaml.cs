namespace EPaper_Loader;

public partial class ImagePreview : ContentPage
{
	public ImagePreview()
	{
		InitializeComponent();
	}

    private void ContentPage_NavigatedTo(object sender, NavigatedToEventArgs e)
    {
		if (AppShell.Shell_isDisplayConnected())
		{
            InfoTable.IsVisible = true;
        }
		else
		{
			InfoTable.IsVisible = false;
		}
    }
}