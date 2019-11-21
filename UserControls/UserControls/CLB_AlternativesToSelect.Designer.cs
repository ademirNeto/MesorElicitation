using System.Collections.Generic;
namespace UserControls {
    partial class CLB_AlternativesToSelect {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose (bool disposing) {
            if(disposing && (components != null)) {
                components.Dispose ();
            }
            base.Dispose (disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent () {
            this.CLB_items = new System.Windows.Forms.CheckedListBox();
            this.SuspendLayout();
            // 
            // CLB_items
            // 
            this.CLB_items.CheckOnClick = true;
            this.CLB_items.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CLB_items.FormattingEnabled = true;
            this.CLB_items.HorizontalScrollbar = true;
            this.CLB_items.Items.AddRange(new object[] {
            "Marcar todos"});
            this.CLB_items.Location = new System.Drawing.Point(0, 0);
            this.CLB_items.Name = "CLB_items";
            this.CLB_items.Size = new System.Drawing.Size(150, 150);
            this.CLB_items.TabIndex = 35;
            this.CLB_items.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.CLB_items_ItemCheck);
            // 
            // CLB_AlternativesToSelect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.CLB_items);
            this.Name = "CLB_AlternativesToSelect";
            this.ResumeLayout(false);

        }

        #endregion

        public List<string> retornaSelecionados(){
            List<string> selecionados = new List<string>();
            for (int i = 1; i < this.CLB_items.Items.Count; i++) {//começa do (i=1) para não colocar o (des)marcar todos na lista de selecionados
                if (this.CLB_items.GetItemChecked(i) ==  true)
                    selecionados.Add(this.CLB_items.GetItemText(i));
            }            
            return selecionados;
        }
        
        private System.Windows.Forms.CheckedListBox CLB_items;
    }
}
