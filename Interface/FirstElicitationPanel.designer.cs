namespace InterfaceUnificada
{
    partial class FirstElicitationPanel
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
            this.GB_minmax = new System.Windows.Forms.GroupBox();
            this.TB_Intervals = new System.Windows.Forms.TextBox();
            this.LB_partes = new System.Windows.Forms.Label();
            this.TB_ValorMaximo = new System.Windows.Forms.TextBox();
            this.TB_ValorMinimo = new System.Windows.Forms.TextBox();
            this.LB_valorMaximo = new System.Windows.Forms.Label();
            this.LB_valorMinimo = new System.Windows.Forms.Label();
            this.BT_Avançar = new System.Windows.Forms.Button();
            this.PN_startElicitationFirmDirecBisec = new System.Windows.Forms.Panel();
            this.PN_start_another = new System.Windows.Forms.Panel();
            this.BT_bissection_avancar = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.GB_minmax.SuspendLayout();
            this.PN_startElicitationFirmDirecBisec.SuspendLayout();
            this.PN_start_another.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // GB_minmax
            // 
            this.GB_minmax.Controls.Add(this.TB_Intervals);
            this.GB_minmax.Controls.Add(this.LB_partes);
            this.GB_minmax.Controls.Add(this.TB_ValorMaximo);
            this.GB_minmax.Controls.Add(this.TB_ValorMinimo);
            this.GB_minmax.Controls.Add(this.LB_valorMaximo);
            this.GB_minmax.Controls.Add(this.LB_valorMinimo);
            this.GB_minmax.Location = new System.Drawing.Point(11, 13);
            this.GB_minmax.Name = "GB_minmax";
            this.GB_minmax.Size = new System.Drawing.Size(200, 118);
            this.GB_minmax.TabIndex = 4;
            this.GB_minmax.TabStop = false;
            this.GB_minmax.Text = "Limites de Valores da Variável";
            // 
            // TB_Intervals
            // 
            this.TB_Intervals.Enabled = false;
            this.TB_Intervals.Location = new System.Drawing.Point(89, 81);
            this.TB_Intervals.Name = "TB_Intervals";
            this.TB_Intervals.Size = new System.Drawing.Size(76, 20);
            this.TB_Intervals.TabIndex = 8;
            this.TB_Intervals.Text = "4";
            this.TB_Intervals.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox_keyPress);
            // 
            // LB_partes
            // 
            this.LB_partes.AutoSize = true;
            this.LB_partes.Location = new System.Drawing.Point(6, 81);
            this.LB_partes.Name = "LB_partes";
            this.LB_partes.Size = new System.Drawing.Size(83, 13);
            this.LB_partes.TabIndex = 7;
            this.LB_partes.Text = "N° de Intervalos";
            // 
            // TB_ValorMaximo
            // 
            this.TB_ValorMaximo.Location = new System.Drawing.Point(89, 55);
            this.TB_ValorMaximo.Name = "TB_ValorMaximo";
            this.TB_ValorMaximo.Size = new System.Drawing.Size(76, 20);
            this.TB_ValorMaximo.TabIndex = 6;
            this.TB_ValorMaximo.Text = "1.0";
            this.TB_ValorMaximo.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox_keyPress);
            // 
            // TB_ValorMinimo
            // 
            this.TB_ValorMinimo.Location = new System.Drawing.Point(89, 28);
            this.TB_ValorMinimo.Name = "TB_ValorMinimo";
            this.TB_ValorMinimo.Size = new System.Drawing.Size(76, 20);
            this.TB_ValorMinimo.TabIndex = 2;
            this.TB_ValorMinimo.Text = "0.0";
            this.TB_ValorMinimo.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox_keyPress);
            // 
            // LB_valorMaximo
            // 
            this.LB_valorMaximo.AutoSize = true;
            this.LB_valorMaximo.Location = new System.Drawing.Point(6, 55);
            this.LB_valorMaximo.Name = "LB_valorMaximo";
            this.LB_valorMaximo.Size = new System.Drawing.Size(70, 13);
            this.LB_valorMaximo.TabIndex = 5;
            this.LB_valorMaximo.Text = "Valor Máximo";
            // 
            // LB_valorMinimo
            // 
            this.LB_valorMinimo.AutoSize = true;
            this.LB_valorMinimo.Location = new System.Drawing.Point(6, 31);
            this.LB_valorMinimo.Name = "LB_valorMinimo";
            this.LB_valorMinimo.Size = new System.Drawing.Size(67, 13);
            this.LB_valorMinimo.TabIndex = 4;
            this.LB_valorMinimo.Text = "Valor Minimo";
            // 
            // BT_Avançar
            // 
            this.BT_Avançar.Location = new System.Drawing.Point(217, 108);
            this.BT_Avançar.Name = "BT_Avançar";
            this.BT_Avançar.Size = new System.Drawing.Size(75, 23);
            this.BT_Avançar.TabIndex = 7;
            this.BT_Avançar.Text = "Next";
            this.BT_Avançar.UseVisualStyleBackColor = true;
            this.BT_Avançar.Click += new System.EventHandler(this.BT_Avançar_Click);
            this.BT_Avançar.KeyDown += new System.Windows.Forms.KeyEventHandler(this.BT_Avançar_KeyDown);
            // 
            // PN_startElicitationFirmDirecBisec
            // 
            this.PN_startElicitationFirmDirecBisec.BackColor = System.Drawing.Color.White;
            this.PN_startElicitationFirmDirecBisec.Controls.Add(this.GB_minmax);
            this.PN_startElicitationFirmDirecBisec.Controls.Add(this.BT_Avançar);
            this.PN_startElicitationFirmDirecBisec.Location = new System.Drawing.Point(1, -1);
            this.PN_startElicitationFirmDirecBisec.Name = "PN_startElicitationFirmDirecBisec";
            this.PN_startElicitationFirmDirecBisec.Size = new System.Drawing.Size(728, 181);
            this.PN_startElicitationFirmDirecBisec.TabIndex = 8;
            // 
            // PN_start_another
            // 
            this.PN_start_another.BackColor = System.Drawing.Color.White;
            this.PN_start_another.Controls.Add(this.BT_bissection_avancar);
            this.PN_start_another.Controls.Add(this.groupBox1);
            this.PN_start_another.Location = new System.Drawing.Point(1, 186);
            this.PN_start_another.Name = "PN_start_another";
            this.PN_start_another.Size = new System.Drawing.Size(728, 181);
            this.PN_start_another.TabIndex = 9;
            // 
            // BT_bissection_avancar
            // 
            this.BT_bissection_avancar.Location = new System.Drawing.Point(217, 95);
            this.BT_bissection_avancar.Name = "BT_bissection_avancar";
            this.BT_bissection_avancar.Size = new System.Drawing.Size(75, 23);
            this.BT_bissection_avancar.TabIndex = 4;
            this.BT_bissection_avancar.Text = "Next";
            this.BT_bissection_avancar.UseVisualStyleBackColor = true;
            this.BT_bissection_avancar.Click += new System.EventHandler(this.BT_bissection_firmino_avancar_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox1);
            this.groupBox1.Controls.Add(this.textBox2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Location = new System.Drawing.Point(11, 18);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Limites de Valores da Variável";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(89, 55);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(76, 20);
            this.textBox1.TabIndex = 6;
            this.textBox1.Text = "1.0";
            this.textBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox_keyPress);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(89, 28);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(76, 20);
            this.textBox2.TabIndex = 2;
            this.textBox2.Text = "0.0";
            this.textBox2.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox_keyPress);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(70, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Valor Máximo";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 31);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(67, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Valor Minimo";
            // 
            // FirstElicitationPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(790, 364);
            this.Controls.Add(this.PN_start_another);
            this.Controls.Add(this.PN_startElicitationFirmDirecBisec);
            this.Name = "FirstElicitationPanel";
            this.Text = "FirstElicitationPanel";
            this.GB_minmax.ResumeLayout(false);
            this.GB_minmax.PerformLayout();
            this.PN_startElicitationFirmDirecBisec.ResumeLayout(false);
            this.PN_start_another.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox GB_minmax;
        private System.Windows.Forms.TextBox TB_ValorMaximo;
        private System.Windows.Forms.TextBox TB_ValorMinimo;
        private System.Windows.Forms.Label LB_valorMaximo;
        private System.Windows.Forms.Label LB_valorMinimo;
        private System.Windows.Forms.Button BT_Avançar;
        private System.Windows.Forms.Label LB_partes;
        private System.Windows.Forms.TextBox TB_Intervals;
        public System.Windows.Forms.Panel PN_startElicitationFirmDirecBisec;
        public System.Windows.Forms.Panel PN_start_another;
        private System.Windows.Forms.Button BT_bissection_avancar;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
    }
}