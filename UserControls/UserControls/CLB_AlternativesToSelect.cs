using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
//using InterfaceUnificada;

namespace UserControls {
    public partial class CLB_AlternativesToSelect : UserControl {
        public CLB_AlternativesToSelect()
        {
            InitializeComponent();
            CLB_items.SetItemChecked(0, true);            
            //this.CLB_items.Items.Clear ();
        }
        public void addItem(string label)
        {
            this.CLB_items.Items.Add(label, true);
        }
        public void addItems(string[] labels)
        {
            //int length = labels.Count();
            for (int i = 0; i < labels.Count(); i++) {
                this.addItem(labels[i]);
            }
        }
        public void addlastItem(string label, string[] lista)
        {
            this.CLB_items.Items.Insert(lista.Length + 1, label);
        }

        private void CLB_items_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (e.Index == 0){
                if (CLB_items.GetItemChecked(0)) {
                    IEnumerator myEnumerator;
                    myEnumerator = CLB_items.CheckedIndices.GetEnumerator(); int y;                    
                    myEnumerator.MoveNext();
                    while (myEnumerator.MoveNext() != false) {
                        y = (int)myEnumerator.Current;
                        CLB_items.SetItemChecked(y, false);
                    }
                    myEnumerator.Reset();
                    CLB_items.SetItemChecked(0, true);
                }
                else if (CLB_items.GetItemChecked(0) == false){
                    for (int i = 1; i < CLB_items.Items.Count; i++){
                        CLB_items.SetItemChecked(i, true);
                    }
                    CLB_items.SetItemChecked(0, false);
                }
            }
        }
    }
}
