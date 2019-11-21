using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace InterfaceUnificada
{
    public class ElicitationHelper
    {
        private static ElicitationHelper _instance;
        private IFormPrincipal ifPrincipal;

        private ElicitationHelper()
        {

        }

        private ElicitationHelper(IFormPrincipal ifPrincipal)
        {
            this.ifPrincipal = ifPrincipal;
        }

        static ElicitationHelper instance(IFormPrincipal ifPrincipal)
        {
            if(_instance == null)
                _instance = new ElicitationHelper(ifPrincipal);

            return _instance;
        }

        public static double[] doubleXVector (double[] x) {
            double[] tmpX = new double[2 * x.Length-2];
            int j = 1;
            for(int i = 0; i < x.Length-1; i++) {
                tmpX[j - 1] = x[i]; tmpX[j] = x[i + 1];
                j += 2;
            }
            return tmpX;
        }
        
        public static double[] unDoubleXVector(double[] doubleX) {
            int n = doubleX.Length;
            double[] tmpX = new double[(n+2)/2];
            int i,j;
            for(i = j = 0; i < n; i+=2,j++) {
                tmpX[j] = doubleX[i];
            }
            tmpX[j] = doubleX[i-1];
            return tmpX;
        }
        public static double[] doubleYVector (double[] y) {
            double[] tmpy = new double[2 * y.Length-2];
            int j = 1;
            for(int i = 0; i < y.Length-1; i++) {
                tmpy[j - 1] = y[i]; tmpy[j] = y[i];
                j += 2;
            }
            return tmpy;
        }

        public static double[] doubleYVector(double[] Fx, double[] x){
            int length = Fx.Length;
            double[] tmpY = new double[2 * length-2];
            int j = 1;
            for (int i = 1; i < length; i++){
                double delta = x[i] - x[i-1];
                double prob = Fx[i] - Fx[i-1];
                double f_i = prob/delta;
                tmpY[j - 1] = f_i; tmpY[j] = f_i;
                j += 2;
            }
            return tmpY;
        }

        public static double[] getCumulative(double[] prob)
        {
            int n = prob.Length;
            double[] Fx = new double[n];
            Fx[0] =0;
            for (int i = 1; i < n; i++)
                Fx[i] = Fx[i-1] + prob[i];
            if(Fx[n-1] != 1) {//a distribuição prob está desnormalizada
                for(int i = 1; i < n; i++)
                    Fx[i]/=Fx[n-1];
            }

            return Fx;
        }

        public static string[] buildStatistics(double[] x, double[] Fx, double[] doubleX, double[] doublefx, int numberInterval, double min, double max)
        {
            int nPoints = 2 * numberInterval; //Numero de pontos no grafico
            string [] lista = new string[2 * nPoints + 7];//Tamanho da string 
            int t = 0;
            lista[t] = min.ToString(); t++;
            lista[t] = max.ToString(); t++;
            lista[t] = nPoints.ToString();
            t++;
            int j = 0;
            while (j < nPoints)
            {
                lista[t] = doubleX[j].ToString();
                lista[t + 1] = doublefx[j].ToString();
                t += 2;
                j++;    
            }
            
            string q2 = Engine.EngineInterface.getMeasuresFromPDF(x, Fx, numberInterval+1);//gerando as estatisticas
            string[] lista0 = q2.Split(new char[] { ';' });

            j = 0;
            while (j < 4)
            {
                lista[t] = lista0[j];
                j++;
                t++;
            }

            return lista;
        }

        public static string[] buildStatistics(double[] x, double[] Fx, int numberInterval, double min, double max)
        {   //TODO: this code seems to be buged... To talk with Nielson.
            int nPoints = 2 * numberInterval; //Numero de pontos no grafico
            string[] lista = new string[2 * nPoints + 8];//Tamanho do array de strings
            double[] doubleX; doubleX = doubleXVector(x);
            double[] doublefx; doublefx = doubleYVector(Fx, x);

            int t = 0;
            lista[t] = min.ToString(); t++;
            lista[t] = max.ToString(); t++;
            lista[t] = nPoints.ToString();
            t++;
            int j = 0;
            while (j < nPoints)
            {
                lista[t] = doubleX[j].ToString();
                lista[t + 1] = doublefx[j].ToString();
                t += 2;
                j++;
            }

            string q2 = Engine.EngineInterface.getMeasuresFromPDF(x, Fx, numberInterval + 1);//gerando as estatisticas
            string[] lista0 = q2.Split(new char[] { ';' });

            j = 0;
            while (j < lista0.Length)
            {
                lista[t] = lista0[j];
                j++;
                t++;
            }

            return lista;
        }

        public static double[] updateCredibilitiesDirectMethod(double [] creds, int indexIncremented){
            int n = creds.Length;
            double[] tmpCreds = new double[n];
            double sumCreds = 0;
            double signedCred = creds[indexIncremented];
            double restCred = 1 - signedCred;
            creds[indexIncremented] = 0;
            for (int i = 0; i < n; i++)
            {
                sumCreds += creds[i];
            }

            if (sumCreds <= 0)
            {
                for (int i = 0; i < n; i++)
                {
                    tmpCreds[i] = restCred/(n-1);
                }
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    tmpCreds[i] = (creds[i]/sumCreds)*restCred;
                }
            }
            tmpCreds[indexIncremented] = signedCred;
            return tmpCreds;
        
        }

        public static double[] updateCredibilitiesDirectMethod(double[] creds) {
            int n = creds.Length;
            double[] tmpCreds = new double[n];
            double sumCreds = creds.Sum();
            
            for (int i = 0; i < n; i++) {
                tmpCreds[i] = (creds[i] / sumCreds);
            }
            
            return tmpCreds;

        }

        public static double[] getCredibilities(double [] doubleX, double [] doubleY){
            int n = doubleX.Length;
            double[] Creds = new double[(n/2)];
            int i, j;
            for(i = j = 0; i < n; i+=2, j++) {
                double x_ = doubleX[i + 1] - doubleX[i];
                double y_ = doubleY[i + 1];
                Creds[j] = x_ * y_;
            }

            return Creds;
        }

    }
}
