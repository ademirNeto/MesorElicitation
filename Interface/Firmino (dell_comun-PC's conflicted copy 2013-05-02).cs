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
        //private Variable variable;

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
        }

        public void showMainPanel(double min, double center, double max, double cred, int index)
        {
            InitializeComponent();
            //this.q = varName;
            string q2 = Engine.EngineInterface.getNextBinaryQuestion(min, center, max, cred, index, Engine.EngineInterface.FIRMINO);

            this.lista = q2.Split(new char[] { ';' });
            this.p.min = Convert.ToDouble(lista[0]);
            this.p.max = Convert.ToDouble(lista[1]);
            this.p.center = (min + max) / 2.0;
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
                Engine.EngineInterface.deleteChildren(this.min, this.center, this.max);
            } catch (Exception exc) {
                MessageBox.Show(exc.Message + "-----------\n" + exc.StackTrace);
            }
            //IMethod method = methodManager.getCurrentMethod();
            //this.ifPrincipal.removeLastIteraction();
            //RB_semPreferencia.Checked = false;
        }


        //override public bool FinishMethod()
        //{
        //    try
        //    {
        //        InterfaceBanco banco = InterfaceBanco.getInstance();//salvando no banco

        //        int j = 0;
        //        for (int i = 0; i < this.answers.Count; i++)
        //        {
        //            banco.inserirResposta(1, answers[i], times[i], creds[i]);//implementar metodo para ver o id da pergunta
        //            banco.inserirEstatistica(statistics[j], statistics[j + 1], statistics[j + 2], statistics[j + 3]);
        //            j += 4;
        //        }

        //        string[] parametros = question.distribuicao.Split(new char[] { ';' });
        //        ParesAcumulados paresAcumulados = new ParesAcumulados();
        //        ArrayList arraylist = paresAcumulados.RetornaFx(x, y);
        //        Fx = (double[])arraylist[0];
        //        x_ = (double[])arraylist[1];

        //        double[] Fx_real = paresAcumulados.getRealCDF(this.question.distribuicao, x_);
        //        banco.inserirParesAcumulados(x_, Fx, Fx_real);
        //    }
        //    catch
        //    {
        //        ifPrincipal.DisplayMessage(DefaultConfig.ST_TXT_ERROR_SAVE_BANK, true);
        //        return false;
        //    }
        //    return true;
        //}

        override public bool getFinishedMethod()
        {
            return true;
        }

        override public int getElicitationMethod()
        {
            return CalibrationEngine.CalibrationInterface.MethodType.FIRMINO;
        }

        //override public int 

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
            //ifPrincipal.getWatch().Stop();
            //this.p.timeConsumption = ifPrincipal.getWatch().ElapsedMilliseconds;//medir o tempo da iteração
            //ifPrincipal.getWatch().Restart();
            string resposta = this.RB_MinMidle.Text.Substring(2, RB_MinMidle.Text.Length - 9).Replace(',', ';');
            par.creds.Add(cred);
            par.cred = cred;
            par.center = (this.p.min + this.p.max) / 2;
            par.answers.Add(resposta);
            par.times.Add(this.p.timeConsumption / 1000);//Armazenar nas listas os valores do tempo consumido e das respostas
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 8]));
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 7]));
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 6]));
            par.statistics.Add(Convert.ToDouble(lista[lista.Length - 5]));
            par.iteracao += 1;
            par.x = this.x;
            
            //this.p.W = new double[4]{cred,1-cred};
            int index = 0;
            double newMin = this.p.min, newMax = this.p.center;
            if (this.RB_MidleMax.Checked == true)
            {
                //RB_MidleMax.Checked = false;
                index = 1;
                resposta = this.RB_MidleMax.Text.Substring(2, RB_MidleMax.Text.Length - 6).Replace(',', ';');
            }

            par.index = index;

            return new Firmino(par, this.ifPrincipal);
        }

        private void RB_MinMidle_CheckedChanged(object sender, EventArgs e) {

        }

        private void RB_MidleMax_CheckedChanged(object sender, EventArgs e) {

        }
    }
}
