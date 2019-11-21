namespace UserControls
{
    partial class TBCursos
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
            this.CB_Curso = new System.Windows.Forms.ComboBox();
            this.BT_MoreTitulacao = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.TB_Especialidade = new System.Windows.Forms.TextBox();
            this.CB_concluido = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // CB_Curso
            // 
            this.CB_Curso.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CB_Curso.FormattingEnabled = true;
            this.CB_Curso.Location = new System.Drawing.Point(48, 44);
            this.CB_Curso.Name = "CB_Curso";
            this.CB_Curso.Size = new System.Drawing.Size(406, 21);
            this.CB_Curso.TabIndex = 21;
            // 
            // BT_MoreTitulacao
            // 
            this.BT_MoreTitulacao.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold);
            this.BT_MoreTitulacao.Location = new System.Drawing.Point(460, 2);
            this.BT_MoreTitulacao.Name = "BT_MoreTitulacao";
            this.BT_MoreTitulacao.Size = new System.Drawing.Size(20, 21);
            this.BT_MoreTitulacao.TabIndex = 19;
            this.BT_MoreTitulacao.Text = "+";
            this.BT_MoreTitulacao.UseVisualStyleBackColor = true;
            this.BT_MoreTitulacao.Click += new System.EventHandler(this.BT_MoreTitulacao_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 10);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(34, 13);
            this.label3.TabIndex = 20;
            this.label3.Text = "Curso";
            // 
            // TB_Especialidade
            // 
            this.TB_Especialidade.Location = new System.Drawing.Point(48, 3);
            this.TB_Especialidade.Name = "TB_Especialidade";
            this.TB_Especialidade.Size = new System.Drawing.Size(406, 20);
            this.TB_Especialidade.TabIndex = 18;
            // 
            // CB_concluido
            // 
            this.CB_concluido.AutoSize = true;
            this.CB_concluido.Checked = true;
            this.CB_concluido.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CB_concluido.Location = new System.Drawing.Point(48, 80);
            this.CB_concluido.Name = "CB_concluido";
            this.CB_concluido.Size = new System.Drawing.Size(75, 17);
            this.CB_concluido.TabIndex = 22;
            this.CB_concluido.Text = "Concluído";
            this.CB_concluido.UseVisualStyleBackColor = true;
            // 
            // TBCursos
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.CB_concluido);
            this.Controls.Add(this.CB_Curso);
            this.Controls.Add(this.BT_MoreTitulacao);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.TB_Especialidade);
            this.Name = "TBCursos";
            this.Size = new System.Drawing.Size(486, 104);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button BT_MoreTitulacao;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox TB_Especialidade;
        public System.Windows.Forms.ComboBox CB_Curso;
        private System.Windows.Forms.CheckBox CB_concluido;
    }
}
