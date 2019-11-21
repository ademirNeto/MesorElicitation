using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace InterfaceUnificada {
    public partial class FirstElicitationPanel : Form, IMethod, IPanelMethod, IMethodManager {
        public Boolean verificar = false;
        public double min, max;
        public int k;
        public List<double> times = new List<double>();
        public List<string> answers = new List<string>();
        public List<double> statistics = new List<double>();
        public Question question;
        public Process process;

        public FirstElicitationPanel direto1;

        //---
        IFormPrincipal ifPrincipal;
        ElicitationMethod elicitationMethod;
        IMethod currentMethod;
        public List<IMethod> MethodNode = new List<IMethod>(0);
        List<Panel> firstPanelList = new List<Panel>();
        public Access access = Access.getInstance();

        public FirstElicitationPanel() {
            InitializeComponent();
        }

        public FirstElicitationPanel(IFormPrincipal iformPrincipal) {
            InitializeComponent();
            this.ifPrincipal = iformPrincipal;
        }

        public FirstElicitationPanel(ElicitationMethod elicitationMethod, IFormPrincipal ifPrincipal) {
            InitializeComponent();
            this.ifPrincipal = ifPrincipal;
            this.elicitationMethod = elicitationMethod;
            firstPanelList.Add(this.PN_startElicitationFirmDirecBisec);

            initFirstPanel(elicitationMethod);

            question = ifPrincipal.getQuestion();

            this.displayChartSeries(question);
            List<double> lines = new List<double>();
            this.ifPrincipal.markChoosableAreaChartSeries(lines);
        }

        protected void displayChartSeries(Question q) {

            if (!q.caminhoImagem.Equals(DefaultConfig.ST_DIST_NULL)) {
                //this.ifPrincipal.DisplayDocument(this.question.caminhoImagem, true);
                String caminhoImagemSerie = this.question.caminhoImagem.Replace(".png", "");
                string[] caminhoSplitted = caminhoImagemSerie.Split(new char[] { '\\' });
                String serieName = caminhoSplitted.Last();
                this.ifPrincipal.displayChartSeries(serieName);
            }
        }

        void initFirstPanel(ElicitationMethod emethod) {
            if (emethod == ElicitationMethod.Firmino || emethod == ElicitationMethod.Bissecao) {
                this.LB_partes.Visible = false;
                this.TB_Intervals.Visible = false;
            }
        }

        private void BT_Avançar_Click(object sender, EventArgs e) {
            new TimeEvent (this.ifPrincipal.getQuestion (), TimeEvent.EventType.LEAVE_FIRST_PANEL_OF_ELICITATION, access.process);
            ElicitationParameters par = new ElicitationParameters();

            try {
                par.min = Convert.ToDouble(TB_ValorMinimo.Text);
                par.max = Convert.ToDouble(TB_ValorMaximo.Text);
                par.rootMin = par.min;
                par.rootMax = par.max;
                k = int.Parse (TB_Intervals.Text);
                par.k = k;
                if (par.min < par.max) {
                    verificar = true;
                } else {
                    ifPrincipal.DisplayMessage(DefaultConfig.ST_TXT_VALUES_IRREGULARS_MINMAX, true);
                    verificar = false;
                }
            } catch {
                throw new Exception(DefaultConfig.ST_TXT_VALUES_TYPE_WROTE);
            }
            try {

                if (verificar == true) {
                    par.index = -1;
                    par.center = (par.min + par.max) / 2;

                    if (elicitationMethod == ElicitationMethod.Direto) {
                        double intervalSize = (par.max - par.min) / k;
                        double[] x = new double[k + 1];//grid
                        double[] W = new double[k + 1];//credibilities
                        x[0] = par.min; x[k] = par.max;
                        W[0] = 0; W[k] = (1.0 / k);//W[0] equal Fx[0], W[1] is the credibility assigned to the first interval, and so on
                        for(int i = 1; i < k; i++) {
                            x[i] = x[i - 1] + intervalSize;
                            W[i] = (1.0 / k);
                        }
                        par.W = W;
                        par.x = x;

                        currentMethod = (IMethod)new Direto2 (par, this.ifPrincipal);
                    } else if (elicitationMethod == ElicitationMethod.Bissecao) {
                        par.x = new double[] { par.min, par.max };
                        currentMethod = (IMethod)new Bisection(par, this.ifPrincipal);
                    } else if (elicitationMethod == ElicitationMethod.Firmino) {
                        currentMethod = (IMethod)new Firmino(par, this.ifPrincipal);
                    }
                    currentMethod.sendRerefence(this);

                    this.ifPrincipal.addNewIteraction(currentMethod); //Mostra na tela os campos para por os intervalos.


                }
            } catch (Exception exc) {
                ifPrincipal.DisplayMessage(exc.StackTrace, true);
            }

        }

        public void addNewReference(IMethod method) {
            currentMethod = method;
            this.MethodNode.Add(method);
        }

        public Control getPanel() {
            return this.PN_startElicitationFirmDirecBisec;
        }

        public Double[] getCredibilities() {
            
            return currentMethod.getCredibilities();
        }

        public double getCorrectBin(string parameter) {
            return currentMethod.getCorrectBin(parameter);
        }

        public bool getFinishedMethod() {
            if (currentMethod == null)
                return false;
            return currentMethod.getFinishedMethod();
        }

        public int getElicitationMethod() {
            return CalibrationEngine.CalibrationInterface.MethodType.DIRECT;//TODO: by PRAF: Nielson, este método parece estar bugado... ele sempre retorna o método direto...
        }

        public bool FinishMethod() {
            return currentMethod.FinishMethod();
        }

        public Control getDecisionPanel() {
            if (elicitationMethod == ElicitationMethod.Firmino || elicitationMethod == ElicitationMethod.Direto || elicitationMethod == ElicitationMethod.Bissecao) {
                return firstPanelList[0];
            } else {
                return null;
            }
        }

        public Control getHistogramPanel() {
            return null;
        }

        public void setQuestionAlternatives() {
            this.currentMethod.setQuestionAlternatives ();
            //throw new NotImplementedException();
        }

        public Control getFirstPanel() {
            throw new NotImplementedException();
        }
        public double[] getTrueDistribution(Question question) {

            throw new NotImplementedException();
        }
        public void setHistogramStatistics(Statistics statistics) {
            currentMethod.setHistogramStatistics(statistics);
        }

        private void BT_bissection_firmino_avancar_Click(object sender, EventArgs e) {
            new TimeEvent(this.ifPrincipal.getQuestion(), TimeEvent.EventType.LEAVE_FIRST_PANEL_OF_ELICITATION, access.process);

            ElicitationParameters p = new ElicitationParameters();

            try {
                p.max = Convert.ToDouble(TB_ValorMaximo.Text);
                p.min = Convert.ToDouble(TB_ValorMinimo.Text);
                if (p.min < p.max)
                    verificar = true;
                else
                    ifPrincipal.DisplayMessage(DefaultConfig.ST_TXT_VALUES_IRREGULARS_MINMAX, true);
            } catch {
                ifPrincipal.DisplayMessage(DefaultConfig.ST_TXT_VALUES_TYPE_WROTE, true);
            }

            if (verificar == true) {

                string resposta = TB_ValorMinimo.Text + ';' + TB_ValorMaximo.Text;

                p.center = (p.max + p.min) / 2;
                p.index = -1;
                //p.times.Add(timeComsumption / 1000);
                p.answers.Add(resposta);
                p.creds.Add(0.0);//Passando credibilidade nula para não construir outra condicional no momento do back
                //statistics.Add(0);//passando estatistica nula para não desagrupar as respostas e estatisticas
                p.statistics.AddRange(new double[4] { 0, 0, 0, 0 });
                p.W = new double[2] { 0, 0 };

                this.ifPrincipal.addNewIteraction(currentMethod);
            }
        }


        public void sendRerefence(IMethodManager iMethManager) {
            throw new NotImplementedException();
        }


        public IMethod removeLastReference() {
            currentMethod = null;
            if(MethodNode.Count>0){
                MethodNode.RemoveAt(MethodNode.Count - 1);
            }
            if (MethodNode.Count > 0) {
                currentMethod = MethodNode[MethodNode.Count-1];
            }
            return currentMethod;

        }

        bool IsNull(object obj) {
            if (obj == null)
                throw new Exception("Object is nulll");
            return false;
        }


        public double[] getX() {
            return currentMethod.getX();
        }

        private void BT_Avançar_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Enter) {
                BT_Avançar_Click(sender, null);
            }
        }

        public List<double> getGrid() {
            return  this.currentMethod.getGrid();
        }

        public void setX(double[] xArray) {
            this.currentMethod.setX (xArray);//TODO: Prof Paulo write: Não sei se está correta essa linha que coloquei...
        }

        public IMethod getCurrentMethod() {
            return this.currentMethod;
        }

        public IMethod getMethodBeforeCurrent() {

            return null;
        }

        public void TextBox_keyPress(object sender, KeyPressEventArgs e){

            if(!Char.IsDigit(e.KeyChar) && e.KeyChar != (char)8 && e.KeyChar != '.'){
                e.Handled = true;
            }
        }

        public ElicitationParameters getStatistics() {
            return currentMethod.getStatistics();
        }
    }
}
