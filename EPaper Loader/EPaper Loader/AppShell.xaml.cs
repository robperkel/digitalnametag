using System.IO.Ports;
using System.Runtime.CompilerServices;

namespace EPaper_Loader
{
    public partial class AppShell : Shell
    {
        private static SerialPort port;
        private static EPaperImageConverter imageConverter;
        public AppShell()
        {
            InitializeComponent();
            imageConverter = new EPaperImageConverter();

            //Init Serial Port
            port = new SerialPort();
            port.BaudRate = 9600;
            port.Parity = Parity.None;
        }

        static public void AssignPortName(string str)
        {
            port.PortName = str;
        }

        static public bool OpenPort()
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

        static public bool IsDisplayConnected()
        {
            return port.IsOpen;
        }

        static public bool EPaperLoadImage(string filename)
        {
            return imageConverter.LoadImage(filename);
        }

        static public string EPaperGetImageSize()
        {
            if (!imageConverter.isValid())
            {
                return "??? x ???";
            }

            string str;

            str = imageConverter.getWidth().ToString();
            str += " x ";
            str += imageConverter.getHeight().ToString();

            return str;
        }

        static public string EPaperGetColorMode()
        {
            if (!imageConverter.isValid())
            {
                return "-1";
            }

            switch (imageConverter.getColors())
            {
                case 2:
                    return "B/W";
                case 3:
                    return "B/W/R";
                case 4:
                    return "B/W/R/Y";
                default:
                    return "???";
            }

            return "???";
        }

        static public void SendToEPaper()
        {
            if (port == null)
            {
                return;
            }

            if (port.IsOpen)
            {
                port.Write(" ");
                for (int y = 0; y < imageConverter.getHeight(); y++)
                {
                    for (int x = 0; x < imageConverter.getWidth(); x++)
                    {
                        char c = imageConverter.getPixel(x, y);
                        port.Write(imageConverter.getPixel(x, y).ToString());
                    }
                }
                port.Write("#");
            }
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
