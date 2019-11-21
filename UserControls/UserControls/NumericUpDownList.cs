using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace UserControls
{
    public partial class NumericUpDownList : UserControl
    {
        private double[] probabilities;
        private string[] lbTextList;
        private ControlCollection NumericList;
        private double minimum = 0;
        private double maximum = 1;
        private int distanceAxisX = 100;
        private Point sizeNumericControls = new Point(236, 50);
        private double increment = 0.01D;
        private int numberControls = 0;

        public double Increment
        {
            get { return increment; }
            set { increment = value; }
        }

        public Point SizeNumericControls
        {
            get { return sizeNumericControls; }
            set { sizeNumericControls = value; }
        }

        public int NumberControls
        {
            get { return numberControls; }
            
            set { 
                    numberControls = value;
                    configInputControls();
                }
        }

        public int Distance
        {
            get { return distanceAxisX; }
            set {
                    distanceAxisX = value;
                    //configInputControls();
                }
        }

        public double Minimum
        {
            get { return minimum; }
            set { minimum = value; }
        }

        public double Maximum
        {
            get { return maximum; }
            set { maximum = value; }
        }

        public string[] LbTextList
        {
            get { return lbTextList; }
            set 
            {
                lbTextList = value;
                initLabels(value);
            }
        }

        public double[] Probabilities
        {
            get { return probabilities; }
            set { 
                probabilities = value;
                initProbabilities(value);
            }
        }

        public NumericUpDownList()
        {
            InitializeComponent();
            this.NumericList = new ControlCollection(this.PN_options);
            this.lbTextList = new string[this.numberControls];
            configInputControls();
        }

        public void configInputControls()
        {
            this.NumericList.Clear();
            this.PN_options.Controls.Clear();

            int EixoX = 10, EixoY = 0;


            NumericUpDownButton tmpNum = null;
            for (int i = 0; i < this.numberControls; i++)
            {
                tmpNum = new NumericUpDownButton();

                tmpNum.Location = new System.Drawing.Point(EixoX, EixoY);
                tmpNum.Name = "NUP_alternative" + i;
                tmpNum.Size = new System.Drawing.Size(this.distanceAxisX - 10, 52);
                tmpNum.TabIndex = 2;

                if (lbTextList != null && i < lbTextList.Length)
                    tmpNum.lb_Text = lbTextList[i];

                tmpNum.Value = ((double)1 / this.numberControls).ToString();
                tmpNum.upper = this.maximum;
                tmpNum.lower = this.minimum;
                tmpNum.increment = this.increment;
                tmpNum.getNumericControl.MouseUp += new MouseEventHandler(OnMouseUpNumericUpDown);
                tmpNum.getNumericControl.KeyUp += new KeyEventHandler(OnKeyUpNumericUpDown);

                EixoX += distanceAxisX;
                this.PN_options.Controls.Add(tmpNum);
                this.NumericList.Add(tmpNum);
            }
            if(tmpNum != null)
                tmpNum.Fixed = false;
        }

        private void initLabels(string[] value)
        {
            if(value != null)
            {
                for (int i = 0; i < this.numberControls; i++)
                {
                    if(i < value.Length)
                        ((NumericUpDownButton)this.PN_options.Controls[i]).lb_Text = value[i];
                }
            }
        }

        private void initProbabilities(double[] value) {
            if(value != null) {
                for(int i = 0; i < this.numberControls; i++) {
                    if(i < value.Length)
                        ((NumericUpDownButton)this.PN_options.Controls[i]).Value = value[i].ToString();
                }
            }
        }

        protected void OnMouseUpNumericUpDown(object sender, MouseEventArgs e)
        {
            this.OnMouseUp(e);
        }

        protected void OnKeyUpNumericUpDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter) {
                updateProbabilities();
                this.OnKeyDown(e);
            } else if (e.KeyCode == Keys.Tab) {
                NumericUpDown nUpDow = (NumericUpDown)sender;
                nUpDow.Select(0, 10);

            }
        }

       public void updateProbabilities()
        {
            try {

                double[] credsFixed = this.getProbabilities(true);
                double[] credsNoFixed = this.getProbabilities(false);
                double[] updatedCreds;
                updatedCreds = updateCredibilitiesDirectMethod(credsNoFixed, credsFixed);

                for (int i = 0; i < numberControls; i++) {
                    NumericUpDownButton tmpNum = ((NumericUpDownButton)this.PN_options.Controls[i]);
                    if(!tmpNum.isFixed())
                        tmpNum.Value = updatedCreds[i].ToString();
                }

            } catch (Exception e) {
                throw e;
            }
        }

       double[] updateCredibilitiesDirectMethod(double[] credsNoFixed, double[] credsFixed)
        {
            int n = credsNoFixed.Length;
           double[] tmpCreds = new double[n];
            try {
                double probToBeDistributed = 1 - credsFixed.Sum();
                double sumCreds = credsNoFixed.Sum();

                for (int i = 0; i < n; i++)
                {
                    tmpCreds[i] = (credsNoFixed[i] / sumCreds) * probToBeDistributed;
                }
                sumCreds = tmpCreds.Sum();
                
            } catch (Exception e) {
                throw e;
            }
            return tmpCreds;

        }

        private Double[] getProbabilities(bool isFixed) {
            double[] signedCredibilities = getProbabilities();
            NumericUpDownButton tmpNum;
            for(int i = 0; i < this.numberControls; i++) {
                tmpNum = ((NumericUpDownButton)this.PN_options.Controls[i]);

                if(isFixed ^ tmpNum.isFixed()) // ^ - XOR Operator
                    signedCredibilities[i] = 0;
            }

            return signedCredibilities;
        }

        public Double[] getProbabilities()
        {
            double[] signedCredibilities = new double[this.numberControls];
            NumericUpDownButton tmpNum;
            for (int i = 0; i < this.numberControls; i++)
            {
                tmpNum = ((NumericUpDownButton)this.PN_options.Controls[i]);
                signedCredibilities[i] = tmpNum.getValue();
            }

            return signedCredibilities;
        }
    }
}
