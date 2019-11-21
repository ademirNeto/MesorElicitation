namespace UserControls
{
    partial class RBPublicPrivate
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.RB_Privado = new System.Windows.Forms.RadioButton();
            this.RB_Publico = new System.Windows.Forms.RadioButton();
            this.SuspendLayout();
            // 
            // RB_Privado
            // 
            this.RB_Privado.AutoSize = true;
            this.RB_Privado.Location = new System.Drawing.Point(3, 26);
            this.RB_Privado.Name = "RB_Privado";
            this.RB_Privado.Size = new System.Drawing.Size(61, 17);
            this.RB_Privado.TabIndex = 3;
            this.RB_Privado.TabStop = true;
            this.RB_Privado.Text = "Privado";
            this.RB_Privado.UseVisualStyleBackColor = true;
            // 
            // RB_Publico
            // 
            this.RB_Publico.AutoSize = true;
            this.RB_Publico.Location = new System.Drawing.Point(3, 3);
            this.RB_Publico.Name = "RB_Publico";
            this.RB_Publico.Size = new System.Drawing.Size(60, 17);
            this.RB_Publico.TabIndex = 2;
            this.RB_Publico.TabStop = true;
            this.RB_Publico.Text = "Público";
            this.RB_Publico.UseVisualStyleBackColor = true;
            // 
            // RBPublicPrivate
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.RB_Privado);
            this.Controls.Add(this.RB_Publico);
            this.Name = "RBPublicPrivate";
            this.Size = new System.Drawing.Size(65, 50);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.RadioButton RB_Privado;
        public System.Windows.Forms.RadioButton RB_Publico;

    }
}
