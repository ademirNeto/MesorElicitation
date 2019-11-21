using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Threading = System.Threading;
using System.Collections;

namespace UserControls
{
    public partial class NumericUpDownButton : UserControl
    {
        public String Value
        {
            set {
                Decimal outPut = 0;
                bool result = Decimal.TryParse(value.ToString(), out outPut);
                if (result && outPut >= 0)
                {
                    this.numericUpDown1.Value = outPut;
                }
                else
                {
                    this.numericUpDown1.Value = 0;
                }
            }
        }
        public double getValue()
        {
            return double.Parse(this.numericUpDown1.Value.ToString());
        }

        public Boolean Fixed {
            set {
                checkBox1.Checked = value;
            }
            get {
                return checkBox1.Checked;
            }
        }

        public String lb_Text
        {
            get
            {
                return this.LB_txt.Text;
            }
            set
            {
                this.LB_txt.Text = value;
            }
        }

        public double increment {
            get { return double.Parse(this.numericUpDown1.Increment.ToString()); ; } 
            set { 
                this.numericUpDown1.Increment = Decimal.Parse(value.ToString()); 
            } 
        }
        public double lower { 
            get { return double.Parse(this.numericUpDown1.Minimum.ToString()); } 
            set { this.numericUpDown1.Minimum = Decimal.Parse(value.ToString()); } }
        public double upper { 
            get { return double.Parse(this.numericUpDown1.Maximum.ToString()); } 
            set { this.numericUpDown1.Maximum = Decimal.Parse(value.ToString()); } }

        Threading.Thread t;
        Timer timer;
        public NumericUpDown getNumericControl { get { return this.numericUpDown1; } }

        public NumericUpDownButton()
        {
            InitializeComponent();
            timer = new Timer();
        }
        public NumericUpDownButton(double increment, double lower, double upper, double valueTxt, String valueLb)
        {
            InitializeComponent();
            this.increment = increment;
            this.lower = lower;
            this.upper = upper;
            this.numericUpDown1.Text = valueTxt.ToString();
            this.LB_txt.Text = valueLb.ToString();
        }

        void selectText(object sender) {
            ((NumericUpDown)sender).Select(0, numericUpDown1.Value.ToString().Length);
        }

        
        private void numericUpDown1_KeyDown(object sender, KeyEventArgs e) {
            if(e.KeyCode == Keys.Tab || e.KeyCode == Keys.N) {
                selectText(sender);
            }
        }

        private void numericUpDown1_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e) {
            if(e.KeyCode == Keys.Tab) {
                selectText(sender);
            }
        }

        public bool isFixed(){
            return checkBox1.Checked;
        }
        
    }

    public class NumericUpDownExt : NumericUpDown
    {

        public override void UpButton()
        {
            base.UpButton();
        }

        public override void DownButton()
        {
            base.DownButton();
        }
        public IEnumerator getControls()
        {
            return base.Controls.GetEnumerator();
        }

    }
}
