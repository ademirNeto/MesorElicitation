using System.Windows.Forms;
namespace UserControls
{
    partial class NumericUpDownList
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
            this.PN_options = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // PN_options
            // 
            this.PN_options.AutoScroll = true;
            this.PN_options.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PN_options.Location = new System.Drawing.Point(0, 0);
            this.PN_options.Name = "PN_options";
            this.PN_options.Size = new System.Drawing.Size(442, 83);
            this.PN_options.TabIndex = 0;
            // 
            // NumericUpDownList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.PN_options);
            this.Name = "NumericUpDownList";
            this.Size = new System.Drawing.Size(442, 83);
            this.ResumeLayout(false);

        }

        #endregion

        private Panel PN_options;

    }
}
