using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace UserControls
{
    public partial class Form1 : Form
    {
        private NumericUpDownExt numericUpDown1;
        public Form1()
        {
            InitializeComponent();
            InitializeAcceleratedUpDown();

            //IEnumerator controls =  numericUpDown1.getControls();
            //while (controls.MoveNext())
            //{
            //    Control c = (Control)controls.Current;
                
            //}
        }
            
        private void InitializeAcceleratedUpDown()
        {
            //numericUpDown1 = new NumericUpDownExt();
            //numericUpDown1.Location = new Point(40, 40);
            //numericUpDown1.Maximum = 40000;
            //numericUpDown1.Minimum = -40000;
            //// Add some accelerations to the control. 
            //numericUpDown1.Accelerations.Add(new NumericUpDownAcceleration(2, 100));
            ////numericUpDown1.Accelerations.Add(new NumericUpDownAcceleration(5, 1000));
            ////numericUpDown1.Accelerations.Add(new NumericUpDownAcceleration(8, 5000));
            //Controls.Add(numericUpDown1);

        }

        private void Form1_KeyDown(object sender, KeyEventArgs e) {
            
        }
    }
}
