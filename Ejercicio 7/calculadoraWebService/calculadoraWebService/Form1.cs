using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace calculadoraWebService
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void AddNumberToTextBox(string number)
        {
            textBox1.Text += number;
        }


        private void button1_Click_1(object sender, EventArgs e)
        {
            AddNumberToTextBox("1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("2");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("3");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("4");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("5");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("6");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("7");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("8");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("9");
        }

        private void button10_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("0");
        }

        private void button15_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("-");
        }

        private void button16_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("+");
        }

        private void button17_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("*");
        }

        private void button18_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox("/");
        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 0)
            {
                textBox1.Text = textBox1.Text.Substring(0, textBox1.Text.Length - 1);
            }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            AddNumberToTextBox(" ");
        }

        private void button12_Click(object sender, EventArgs e) // Botón INFIJA
        {
            string expresion = textBox1.Text;
            double resultado = EvaluarExpresionInfija(expresion);
            textBox1.Text = resultado.ToString();
        }

        private void button13_Click(object sender, EventArgs e) // Botón PREFIJA
        {
            string expresion = textBox1.Text;
            double resultado = EvaluarExpresionPrefija(expresion);
            textBox1.Text = resultado.ToString();
        }

        // Función para evaluar la expresión infija
        private double EvaluarExpresionInfija(string expresion)
        {
            Stack<char> operadores = new Stack<char>();
            Stack<double> valores = new Stack<double>();

            for (int i = 0; i < expresion.Length; i++)
            {
                if (char.IsDigit(expresion[i]))
                {
                    StringBuilder sb = new StringBuilder();

                    // Manejar números de más de un dígito
                    while (i < expresion.Length && (char.IsDigit(expresion[i]) || expresion[i] == '.'))
                    {
                        sb.Append(expresion[i++]);
                    }
                    i--;

                    valores.Push(double.Parse(sb.ToString()));
                }
                else if (expresion[i] == '(')
                {
                    operadores.Push(expresion[i]);
                }
                else if (expresion[i] == ')')
                {
                    while (operadores.Peek() != '(')
                    {
                        valores.Push(RealizarOperacion(operadores.Pop(), valores.Pop(), valores.Pop()));
                    }
                    operadores.Pop();
                }
                else if (EsOperador(expresion[i]))
                {
                    while (operadores.Count > 0 && Prioridad(operadores.Peek()) >= Prioridad(expresion[i]))
                    {
                        valores.Push(RealizarOperacion(operadores.Pop(), valores.Pop(), valores.Pop()));
                    }
                    operadores.Push(expresion[i]);
                }
            }

            while (operadores.Count > 0)
            {
                valores.Push(RealizarOperacion(operadores.Pop(), valores.Pop(), valores.Pop()));
            }

            return valores.Pop();
        }

        // Función para evaluar la expresión prefija
        private double EvaluarExpresionPrefija(string expresion)
        {
            Stack<double> stack = new Stack<double>();

            for (int i = expresion.Length - 1; i >= 0; i--)
            {
                if (char.IsDigit(expresion[i]))
                {
                    StringBuilder sb = new StringBuilder();

                    // Manejar números de más de un dígito
                    while (i >= 0 && (char.IsDigit(expresion[i]) || expresion[i] == '.'))
                    {
                        sb.Insert(0, expresion[i--]);
                    }
                    i++;

                    stack.Push(double.Parse(sb.ToString()));
                }
                else if (EsOperador(expresion[i]))
                {
                    double op1 = stack.Pop();
                    double op2 = stack.Pop();
                    stack.Push(RealizarOperacion(expresion[i], op1, op2));
                }
            }

            return stack.Pop();
        }

        private bool EsOperador(char c)
        {
            return c == '+' || c == '-' || c == '*' || c == '/';
        }

        private int Prioridad(char operador)
        {
            if (operador == '+' || operador == '-')
                return 1;
            if (operador == '*' || operador == '/')
                return 2;
            return 0;
        }

        private double RealizarOperacion(char operador, double b, double a)
        {
            switch (operador)
            {
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': return a / b;
                default: throw new InvalidOperationException("Operador inválido");
            }
        }
    }
}
