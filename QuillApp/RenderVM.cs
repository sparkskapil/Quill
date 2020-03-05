using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;
using System.Threading;
using System.Drawing;
using System.Windows.Media.Imaging;
using System.Windows;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Input;

namespace QuillApp
{
    public static class BitmapConversion
    {
        public static BitmapSource BitmapToBitmapSource(Bitmap source)
        {
            return System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(
                          source.GetHbitmap(),
                          IntPtr.Zero,
                          Int32Rect.Empty,
                          BitmapSizeOptions.FromEmptyOptions());
        }

        public static BitmapSource BitmapToBitmapSource(IntPtr source)
        {
            return System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(
                          source,
                          IntPtr.Zero,
                          Int32Rect.Empty,
                          BitmapSizeOptions.FromEmptyOptions());
        }
    }
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
        private BitmapSource frame;
        private NativeEngine.WpfViewPort vp;
        private Thread renderThread;
        public event PropertyChangedEventHandler PropertyChanged;

        public delegate void RenderEventHandler();
        //public event RenderEventHandler ForceRender;

        private ICommand _mouseClick;
        public ICommand MouseClick
        {
            get
            {
                return _mouseClick ?? (_mouseClick = new RelayCommand<object>(
                          x => { OnRender(); }));
            }
        }
        public BitmapSource Frame
        {
            get { return frame; }
            set
            {
                frame = value;
                OnPropertyChanged();
            }
        }
       

        public RenderVM()
        {
            vp = new NativeEngine.WpfViewPort();
            //ForceRender += OnRender;
            renderThread = new Thread(() =>
            {
                vp.setup();
                vp.draw();

            });
            renderThread.Start();
            OnRender();
        }

        protected void OnRender()
        {
            //   System.IO.File.Copy(@"./Frame.png", @"./Frame1.png");
            unsafe{
                int width = 0, height = 0;
                var frame = vp.GetFramBuffer(ref width, ref height);
                var buffer = (IntPtr)frame;
                if(frame != null)
                    Frame = BitmapConversion.BitmapToBitmapSource(buffer);
                else
                {
                    Bitmap bitmap = (Bitmap)Bitmap.FromFile(@"./Frame.png", true);
                    Frame = BitmapConversion.BitmapToBitmapSource(bitmap);
                    bitmap.Dispose();

                }
            }
            
        }

        // Create the OnPropertyChanged method to raise the event
        // The calling member's name will be used as the parameter.
        protected void OnPropertyChanged([CallerMemberName] string name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
