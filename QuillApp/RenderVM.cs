using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace QuillApp
{
    class RenderVM
    {
        //public D3DImage Frame { get; set; }
        NativeEngine.WpfViewPort vp;

        public RenderVM()
        {
            vp = new NativeEngine.WpfViewPort();
        }
    }
}
