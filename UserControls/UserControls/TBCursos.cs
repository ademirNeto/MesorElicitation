using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace UserControls
{
    public partial class TBCursos : UserControl
    {

        public TBCursos()
        {
            InitializeComponent();
        }

        private void BT_MoreTitulacao_Click(object sender, EventArgs e)
        {
            if (TB_Especialidade.Text != "")
            {
                CB_Curso.Items.Add(TB_Especialidade.Text + ";" +(this.CB_concluido.Checked).ToString());
                TB_Especialidade.Text = String.Empty;

            }
        }

        public ComboBox returnCombo() 
        {
            if (TB_Especialidade.Text!="")
                CB_Curso.Items.Add(TB_Especialidade.Text + ";" + (this.CB_concluido.Checked).ToString());
            
            return CB_Curso;
        }

    }
}
