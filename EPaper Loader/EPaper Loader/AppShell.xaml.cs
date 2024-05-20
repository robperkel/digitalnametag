using Microsoft.UI.Composition;
using System.IO.Ports;
using System.Runtime.CompilerServices;

namespace EPaper_Loader
{
    public partial class AppShell : Shell
    {
        private static SerialPort port;
        public AppShell()
        {
            InitializeComponent();

            //Init Serial Port
            port = new SerialPort();
            port.BaudRate = 9600;
            port.Parity = Parity.None;
        }

        static public void Shell_assignPortName(string str)
        {
            port.PortName = str;
        }

        static public bool Shell_openPort()
        {
            if (port.IsOpen)
            {
                return true;
            }

            try
            {
                port.Open();
            }
            catch
            {
                return false;
            }

            return true;
        }

        static public bool Shell_isDisplayConnected()
        {
            return port.IsOpen;
        }

        private void Shell_Disappearing(object sender, EventArgs e)
        {
            if (port != null)
            {
                if (port.IsOpen)
                {
                    port.Close();
                }
            }
        }
    }
}
