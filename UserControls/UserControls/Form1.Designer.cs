using System;
namespace UserControls
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.numericUpDownButtons1 = new UserControls.NumericUpDownButton();
            this.numericUpDownList2 = new UserControls.NumericUpDownList();
            this.SuspendLayout();
            // 
            // numericUpDownButtons1
            // 
            this.numericUpDownButtons1.increment = 0.01D;
            this.numericUpDownButtons1.lb_Text = "\"Testando\"";
            this.numericUpDownButtons1.Location = new System.Drawing.Point(12, 12);
            this.numericUpDownButtons1.lower = 0D;
            this.numericUpDownButtons1.Name = "numericUpDownButtons1";
            this.numericUpDownButtons1.Size = new System.Drawing.Size(98, 52);
            this.numericUpDownButtons1.TabIndex = 1;
            this.numericUpDownButtons1.upper = 100D;
            // 
            // numericUpDownList2
            // 
            this.numericUpDownList2.Distance = 140;
            this.numericUpDownList2.Increment = 0.01D;
            this.numericUpDownList2.LbTextList = new string[] {
        "Testando 111111111111111111",
        "Testando 111111111111111111",
        "Testando 111111111111111111"};
            this.numericUpDownList2.Location = new System.Drawing.Point(12, 94);
            this.numericUpDownList2.Maximum = 1D;
            this.numericUpDownList2.Minimum = 0D;
            this.numericUpDownList2.Name = "numericUpDownList2";
            this.numericUpDownList2.NumberControls = 4;
            this.numericUpDownList2.Probabilities = null;
            this.numericUpDownList2.Size = new System.Drawing.Size(442, 89);
            this.numericUpDownList2.SizeNumericControls = new System.Drawing.Point(236, 50);
            this.numericUpDownList2.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(558, 360);
            this.Controls.Add(this.numericUpDownList2);
            this.Controls.Add(this.numericUpDownButtons1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

        private NumericUpDownButton numericUpDownButtons1;
        private NumericUpDownList numericUpDownList1;
        private NumericUpDownList numericUpDownList2;
    }
}

