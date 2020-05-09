using System;
using System.Threading;
using System.Drawing;
using System.Windows.Media.Imaging;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Input;
using System.IO;
using System.Drawing.Imaging;

namespace QuillApp
{
    public class RelayCommand<T> : ICommand
    {
        private readonly Predicate<T> _canExecute;
        private readonly Action<T> _execute;

        public RelayCommand(Action<T> execute)
           : this(execute, null)
        {
            _execute = execute;
        }

        public RelayCommand(Action<T> execute, Predicate<T> canExecute)
        {
            if (execute == null)
                throw new ArgumentNullException("execute");
            _execute = execute;
            _canExecute = canExecute;
        }

        public bool CanExecute(object parameter)
        {
            return (_canExecute == null) || _canExecute((T)parameter);
        }

        public void Execute(object parameter)
        {
            _execute((T)parameter);
        }

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }
    }
    class RenderVM : INotifyPropertyChanged
    {
        private BitmapImage image;

        private NativeEngine.WpfViewPort vp;

        private Thread renderThread;

        public event PropertyChangedEventHandler PropertyChanged;

        public BitmapImage Image
        {
            get { return image; }
            set
            {
                image = value;
                OnPropertyChanged();
            }
        }
        public RenderVM()
        {
            vp = new NativeEngine.WpfViewPort();

            renderThread = new Thread(() =>
            {
                vp.setup();
                while (true)
                {
                    var start = DateTime.UtcNow;
                    if (vp.frame())
                        break;
                    var end = DateTime.UtcNow;
                    OnRender();


                    var duration = (end - start).Milliseconds;
                    int a = 1;
                }
            });

            renderThread.Start();
        }

        private Bitmap CreateBitmapFromBuffer(int width, int height)
        {
            Bitmap bitmap = new Bitmap(width, height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
            Rectangle rect = new Rectangle(0, 0, width, height);
            BitmapData data = bitmap.LockBits(rect, ImageLockMode.WriteOnly, bitmap.PixelFormat);
            int padding = data.Stride - 3 * width;
            IntPtr buffer = data.Scan0;

            vp.GetFrameBuffer(ref buffer, ref width, ref height);
            bitmap.UnlockBits(data);

            return bitmap;
        }
        protected void OnRender()
        {   
            int width = 1920, height = 990;
            var bitmap = CreateBitmapFromBuffer(width, height);
            using (var memory = new MemoryStream())
            {
                bitmap.Save(memory, ImageFormat.Png);
                memory.Position = 0;
                var bitmapImage = new BitmapImage();
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memory;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();
                bitmapImage.Freeze();
                Image = bitmapImage;
            }
            bitmap.Dispose();
        }

        // Create the OnPropertyChanged method to raise the event
        // The calling member's name will be used as the parameter.
        protected void OnPropertyChanged([CallerMemberName] string name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
