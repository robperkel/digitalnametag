using Microsoft.Maui.Controls.Internals;
using System.IO.Ports;

namespace EPaper_Loader
{
    public partial class MainPage : ContentPage
    {
        private void UpdateCOMListings()
        {
            //Clear existing items
            COMList.Items.Clear();

            string[] strPorts = SerialPort.GetPortNames();

            //Add available COM Ports
            foreach (string s in strPorts)
            {
                COMList.Items.Add(s);
            }
            
            if (COMList.Items.Count > 0)
            {
                COMList.SelectedIndex = 0;
            }
        }

        public MainPage()
        {
            InitializeComponent();
            UpdateCOMListings();
        }

        private void RefreshBtn_Pressed(object sender, EventArgs e)
        {
            UpdateCOMListings();
        }

        private void ConnectBtn_Pressed(object sender, EventArgs e)
        {
            if (COMList.SelectedIndex == -1)
            {
                //No item selected
                ErrorLabel.Text = "Error: A COM Port must be selected!";
                ErrorLabel.IsVisible = true;
                return;
            }

            AppShell.AssignPortName(COMList.Items[COMList.SelectedIndex]);

            if (!AppShell.OpenPort())
            {
                //Unable to open COM Port

                ErrorLabel.Text = "Error: Unable to open COM Port!";
                ErrorLabel.IsVisible = true;
                return;
            }

            //TODO: Communicate with panel!

            ErrorLabel.IsVisible = false;

            Shell.Current.GoToAsync("//ImagePreview");
        }

        private void ContentPage_Unloaded(object sender, EventArgs e)
        {

        }
    }
}
