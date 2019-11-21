using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace UserControls
{
    public partial class RBPublicPrivate : UserControl
    {
        public string decision = "";

        public RBPublicPrivate()
        {
            InitializeComponent();                        
        }

        public string returnDecision()
        {
            if (RB_Privado.Checked) this.decision = "Privado";
            if (RB_Publico.Checked) this.decision = "Público";
            return this.decision;
        }
    }
}
