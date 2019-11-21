namespace InterfaceUnificada
{
    partial class Direto2
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
            this.label9 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.LB_1 = new System.Windows.Forms.Label();
            this.PN_options = new System.Windows.Forms.Panel();
            this.NUDL_options = new UserControls.NumericUpDownList();
            this.PN_Decision.SuspendLayout();
            this.PN_Chart.SuspendLayout();
            this.SuspendLayout();
            // 
            // PN_Decision
            // 
            this.PN_Decision.Controls.Add(this.LB_1);
            this.PN_Decision.Controls.Add(this.NUDL_options);
            this.PN_Decision.Controls.SetChildIndex(this.NUDL_options, 0);
            this.PN_Decision.Controls.SetChildIndex(this.LB_1, 0);
            this.PN_Decision.Controls.SetChildIndex(this.BT_Update, 0);
            this.PN_Decision.Controls.SetChildIndex(this.BT_Finish1, 0);
            this.PN_Decision.Controls.SetChildIndex(this.BT_back, 0);
            // 
            // BT_back1
            // 
            this.BT_back.Location = new System.Drawing.Point(668, 125);
            this.BT_back.TabIndex = 3;
            // 
            // BT_Finish1
            // 
            this.BT_Finish1.Enabled = true;
            this.BT_Finish1.Location = new System.Drawing.Point(747, 125);
            this.BT_Finish1.TabIndex = 12;
            // 
            // BT_Update
            // 
            this.BT_Update.Location = new System.Drawing.Point(590, 125);
            this.BT_Update.Visible = false;
            // 
            // PN_Chart
            // 
            this.PN_Chart.Size = new System.Drawing.Size(868, 208);
            // 
            // MC_histogram
            // 
            this.MC_histogram.Size = new System.Drawing.Size(868, 208);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 99);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(51, 13);
            this.label9.TabIndex = 6;
            this.label9.Text = "Variância";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 72);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(48, 13);
            this.label7.TabIndex = 4;
            this.label7.Text = "Mediana";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(34, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "Moda";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Média";
            // 
            // LB_1
            // 
            this.LB_1.AutoSize = true;
            this.LB_1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LB_1.Location = new System.Drawing.Point(188, 8);
            this.LB_1.Name = "LB_1";
            this.LB_1.Size = new System.Drawing.Size(403, 20);
            this.LB_1.TabIndex = 100;
            this.LB_1.Text = "Atribua suas credibilidades para os seguintes intervalos:";
            // 
            // PN_options
            // 
            this.PN_options.AutoScroll = true;
            this.PN_options.Location = new System.Drawing.Point(12, 428);
            this.PN_options.Name = "PN_options";
            this.PN_options.Size = new System.Drawing.Size(865, 117);
            this.PN_options.TabIndex = 101;
            // 
            // NUDL_options
            // 
            this.NUDL_options.Distance = 100;
            this.NUDL_options.Increment = 0.01D;
            this.NUDL_options.LbTextList = new string[0];
            this.NUDL_options.Location = new System.Drawing.Point(3, 37);
            this.NUDL_options.Maximum = 1D;
            this.NUDL_options.Minimum = 0D;
            this.NUDL_options.Name = "NUDL_options";
            this.NUDL_options.NumberControls = 0;
            this.NUDL_options.Probabilities = null;
            this.NUDL_options.Size = new System.Drawing.Size(871, 90);
            this.NUDL_options.SizeNumericControls = new System.Drawing.Point(236, 50);
            this.NUDL_options.TabIndex = 2;
            this.NUDL_options.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OnKeyUpNumericUpDown);
            // 
            // Direto2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(892, 579);
            this.Controls.Add(this.PN_options);
            this.Name = "Direto2";
            this.Text = "Direto2";
            this.Controls.SetChildIndex(this.PN_options, 0);
            this.Controls.SetChildIndex(this.PN_Decision, 0);
            this.Controls.SetChildIndex(this.PN_Chart, 0);
            this.PN_Decision.ResumeLayout(false);
            this.PN_Decision.PerformLayout();
            this.PN_Chart.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        //private System.Windows.Forms.GroupBox groupBox2;
        //private System.Windows.Forms.Label LB_Var;
        //private System.Windows.Forms.Label LB_Median;
        //private System.Windows.Forms.Label LB_Mode;
        //private System.Windows.Forms.Label LB_Mean;
        private System.Windows.Forms.Button BT_Finish;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label LB_1;
        private System.Windows.Forms.Panel PN_options;
        private UserControls.NumericUpDownList NUDL_options;
    }
}