namespace InterfaceUnificada
 {
     partial class Firmino
     {
         /// <summary>
         /// Required designer variable.
         /// </summary>
         private System.ComponentModel.IContainer components = null;

         /// <summary>
         /// Clean up any resources being used.
         /// </summary>
         /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
         protected override void Dispose (bool disposing)
         {
             if(disposing && (components != null))
             {
                 components.Dispose ();
             }
             base.Dispose (disposing);
         }

         #region Windows Form Designer generated code

         /// <summary>
         /// Required method for Designer support - do not modify
         /// the contents of this method with the code editor.
         /// </summary>
         private void InitializeComponent ()
         {
             this.panel1 = new System.Windows.Forms.Panel();
             this.groupBox1 = new System.Windows.Forms.GroupBox();
             this.label1 = new System.Windows.Forms.Label();
             this.TB_Credibilidade = new System.Windows.Forms.NumericUpDown();
             this.RB_MidleMax = new System.Windows.Forms.RadioButton();
             this.RB_MinMidle = new System.Windows.Forms.RadioButton();
             this.LB_condition = new System.Windows.Forms.Label();
             this.LB_intermediate = new System.Windows.Forms.Label();
             this.PN_Decision.SuspendLayout();
             this.PN_Chart.SuspendLayout();
             this.groupBox1.SuspendLayout();
             ((System.ComponentModel.ISupportInitialize)(this.TB_Credibilidade)).BeginInit();
             this.SuspendLayout();
             // 
             // PN_Decision
             // 
             this.PN_Decision.Controls.Add(this.groupBox1);
             this.PN_Decision.Controls.Add(this.LB_condition);
             this.PN_Decision.Controls.Add(this.LB_intermediate);
             this.PN_Decision.Size = new System.Drawing.Size(825, 173);
             this.PN_Decision.Controls.SetChildIndex(this.BT_Update, 0);
             this.PN_Decision.Controls.SetChildIndex(this.BT_Finish1, 0);
             this.PN_Decision.Controls.SetChildIndex(this.BT_back, 0);
             this.PN_Decision.Controls.SetChildIndex(this.LB_intermediate, 0);
             this.PN_Decision.Controls.SetChildIndex(this.LB_condition, 0);
             this.PN_Decision.Controls.SetChildIndex(this.groupBox1, 0);
             // 
             // BT_back
             // 
             this.BT_back.Location = new System.Drawing.Point(745, 125);
             // 
             // BT_Update
             // 
             this.BT_Update.Location = new System.Drawing.Point(583, 125);
             // 
             // BT_Finish1
             // 
             this.BT_Finish1.Enabled = true;
             this.BT_Finish1.Location = new System.Drawing.Point(664, 125);
             // 
             // panel1
             // 
             this.panel1.Location = new System.Drawing.Point(0, 0);
             this.panel1.Name = "panel1";
             this.panel1.Size = new System.Drawing.Size(200, 100);
             this.panel1.TabIndex = 0;
             // 
             // groupBox1
             // 
             this.groupBox1.BackColor = System.Drawing.Color.White;
             this.groupBox1.Controls.Add(this.label1);
             this.groupBox1.Controls.Add(this.TB_Credibilidade);
             this.groupBox1.Controls.Add(this.RB_MidleMax);
             this.groupBox1.Controls.Add(this.RB_MinMidle);
             this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
             this.groupBox1.Location = new System.Drawing.Point(6, 48);
             this.groupBox1.Name = "groupBox1";
             this.groupBox1.Size = new System.Drawing.Size(258, 100);
             this.groupBox1.TabIndex = 0;
             this.groupBox1.TabStop = false;
             this.groupBox1.Text = "Decisão";
             // 
             // label1
             // 
             this.label1.AutoSize = true;
             this.label1.Location = new System.Drawing.Point(6, 77);
             this.label1.Name = "label1";
             this.label1.Size = new System.Drawing.Size(83, 15);
             this.label1.TabIndex = 11;
             this.label1.Text = "Credibilidade:";
             // 
             // TB_Credibilidade
             // 
             this.TB_Credibilidade.DecimalPlaces = 2;
             this.TB_Credibilidade.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
             this.TB_Credibilidade.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
             this.TB_Credibilidade.Location = new System.Drawing.Point(103, 70);
             this.TB_Credibilidade.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
             this.TB_Credibilidade.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            65536});
             this.TB_Credibilidade.Name = "TB_Credibilidade";
             this.TB_Credibilidade.Size = new System.Drawing.Size(76, 23);
             this.TB_Credibilidade.TabIndex = 3;
             this.TB_Credibilidade.ThousandsSeparator = true;
             this.TB_Credibilidade.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
             // 
             // RB_MidleMax
             // 
             this.RB_MidleMax.AutoSize = true;
             this.RB_MidleMax.Location = new System.Drawing.Point(6, 42);
             this.RB_MidleMax.Name = "RB_MidleMax";
             this.RB_MidleMax.Size = new System.Drawing.Size(86, 19);
             this.RB_MidleMax.TabIndex = 2;
             this.RB_MidleMax.TabStop = true;
             this.RB_MidleMax.Text = "Midle, Max";
             this.RB_MidleMax.UseVisualStyleBackColor = true;
             // 
             // RB_MinMidle
             // 
             this.RB_MinMidle.AutoSize = true;
             this.RB_MinMidle.Location = new System.Drawing.Point(6, 19);
             this.RB_MinMidle.Name = "RB_MinMidle";
             this.RB_MinMidle.Size = new System.Drawing.Size(83, 19);
             this.RB_MinMidle.TabIndex = 1;
             this.RB_MinMidle.TabStop = true;
             this.RB_MinMidle.Text = "Min, Midle";
             this.RB_MinMidle.UseVisualStyleBackColor = true;
             // 
             // LB_condition
             // 
             this.LB_condition.AutoSize = true;
             this.LB_condition.BackColor = System.Drawing.Color.White;
             this.LB_condition.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
             this.LB_condition.Location = new System.Drawing.Point(3, 6);
             this.LB_condition.Name = "LB_condition";
             this.LB_condition.Size = new System.Drawing.Size(59, 15);
             this.LB_condition.TabIndex = 17;
             this.LB_condition.Text = "Condition";
             // 
             // LB_intermediate
             // 
             this.LB_intermediate.AutoSize = true;
             this.LB_intermediate.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
             this.LB_intermediate.Location = new System.Drawing.Point(3, 28);
             this.LB_intermediate.Name = "LB_intermediate";
             this.LB_intermediate.Size = new System.Drawing.Size(99, 15);
             this.LB_intermediate.TabIndex = 18;
             this.LB_intermediate.Text = "IntermediateText";
             // 
             // Firmino
             // 
             this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
             this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
             this.ClientSize = new System.Drawing.Size(891, 595);
             this.Name = "Firmino";
             this.Text = "Firmino";
             this.PN_Decision.ResumeLayout(false);
             this.PN_Decision.PerformLayout();
             this.PN_Chart.ResumeLayout(false);
             this.groupBox1.ResumeLayout(false);
             this.groupBox1.PerformLayout();
             ((System.ComponentModel.ISupportInitialize)(this.TB_Credibilidade)).EndInit();
             this.ResumeLayout(false);

         }

         #endregion

         //private System.Windows.Forms.GroupBox groupBox2;
         //private System.Windows.Forms.Label // LB_Var;
         //private System.Windows.Forms.Label // LB_Median;
         //private System.Windows.Forms.Label // LB_Mode;
         //private System.Windows.Forms.Label //LB_Mean;
         public System.Windows.Forms.Panel panel1;
         private System.Windows.Forms.GroupBox groupBox1;
         private System.Windows.Forms.Label label1;
         private System.Windows.Forms.NumericUpDown TB_Credibilidade;
         private System.Windows.Forms.RadioButton RB_MidleMax;
         private System.Windows.Forms.RadioButton RB_MinMidle;
         private System.Windows.Forms.Label LB_condition;
         private System.Windows.Forms.Label LB_intermediate;
     }
 }