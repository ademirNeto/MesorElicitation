using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using MySql.Data;
using MySql.Data.MySqlClient;
using System.Diagnostics;

namespace InterfaceUnificada
{
    public partial class Firmino : MainEngineClass
    {
        public double tempo;
        public int i = 2;
        public List<double> creds;

        //Construtor
        public Firmino(ElicitationParameters p, IFormPrincipal ifPrincipal)
        {
            this.ifPrincipal = ifPrincipal;
            this.question = this.ifPrincipal.getQuestion();
            this.p = p.getClone();
            //Este if indica que o método só fará três interações.

            if (p.iteracao >= 3) {
                this.BT_Update.Enabled = false;
            } else {    
                this.BT_Update.Enabled = true;
            }

            showMainPanel(p.min, p.center, p.max, p.cred, p.index);
            this.loadConfigMethodForVariable();
            atualizaSeries();
           
        }

        public void showMainPanel(double min, double center, double max, double cred, int index)
        {
            InitializeComponent();
            string q2 = Engine.EngineInterface.getNextBinaryQuestion(min, center, max, cred, index, Engine.EngineInterface.FIRMINO);

            this.lista = q2.Split(new char[] { ';' });
            this.p.min = Convert.ToDouble(lista[0]);
            this.p.max = Convert.ToDouble(lista[1]);
            this.p.center = (this.p.min + this.p.max) / 2.0;
            int length = this.lista.Length;
            this.LB_condition.Text = lista[length - 4];
            this.LB_intermediate.Text = lista[length - 3];
            this.RB_MinMidle.Text = lista[length - 2];
            this.RB_MidleMax.Text = lista[length - 1];
            
            this.InitializeComponent_DistributionResults(this.lista);
            
        }

        override public bool removeLastCredibility(int index)
        {
            this.creds.RemoveAt(index);
            return true;
        }
        
        public override void BT_back_ClickAction(object sender, EventArgs e) {
            base.BT_back_ClickAction(sender, e);
            try {
                Engine.EngineInterface.deleteChildren(this.p.min, this.p.center, this.p.max);
                IMethod currentMethod = this.methodManager.getCurrentMethod();
                
                if (currentMethod != null) {
                    ((Firmino)this.methodManager.getCurrentMethod()).atualizaSeries();   
                }
                //atualizaSeries();
            } catch (Exception exc) {
                MessageBox.Show(exc.Message + "-----------\n" + exc.StackTrace);
            }
        }

        override public bool getFinishedMethod()
        {
            return true;
        }

        override public int getElicitationMethod()
        {
            return CalibrationEngine.CalibrationInterface.MethodType.FIRMINO;
        }

        override protected IMethod updateMethod()
        {
            double cred;
            Boolean verificar = Double.TryParse(TB_Credibilidade.Text, out cred);
            if (!verificar)
            {
                throw new Exception(DefaultConfig.ST_TXT_VALUES_TYPE_WROTE);
            }
            if(cred < .5){
                throw new Exception("A sua credibilidade dever estar dentro do seguinte intervalo [.5 , 1].");
            }
            if (!(RB_MidleMax.Checked == true || RB_MinMidle.Checked == true))
            {
                throw new Exception(DefaultConfig.ST_TXT_CHANGE_ALTERNATIVE_CREDIBILITY);
            }
            
            ElicitationParameters par = p.getClone();

            int index = 0;
            string resposta = this.RB_MinMidle.Text.Substring (2, RB_MinMidle.Text.Length - 9).Replace (',', ';');

            if(this.RB_MidleMax.Checked == true) {
                index = 1;
                resposta = this.RB_MidleMax.Text.Substring (2, RB_MidleMax.Text.Length - 6).Replace (',', ';');

            }
            par.answers.Add (resposta);

            par.creds.Add(cred);
            par.cred = cred;
            par.center = (par.min + par.max) / 2;
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 8]));
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 7]));
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 6]));
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 5]));
            par.iteracao += 1;
            par.x = this.x;

            par.index = index;

            return new Firmino(par, this.ifPrincipal);
        }

        private void atualizaSeries() {
            List<double> lines = new List<double>();
            lines.Add(this.p.min);
            lines.Add(this.p.center);
            lines.Add(this.p.max);
            this.ifPrincipal.markChoosableAreaChartSeries(lines);
        }
        
        //private void RB_MinMidle_CheckedChanged(object sender, EventArgs e) {
        //    RadioButton rb = (RadioButton)sender;
        //    double[] interval = getIntervals(rb.Text);
            
        //    double media = interval.Max();
        //    if (media < interval[1])
        //        media = interval[0];

        //    List<double> lines = new List<double>();
        //    lines.Add(p.min);
        //    lines.Add(p.center);
        //    lines.Add(p.max);
        //    this.ifPrincipal.markChoosableAreaChartSeries(lines);
            
        //}
    }
}
