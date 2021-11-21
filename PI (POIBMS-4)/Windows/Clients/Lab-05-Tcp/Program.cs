using Lab_05_Tcp.WCFSimplexConsole;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_05_Tcp {
    class Program {
        static void Main(string[] args)
        {
            WCFSimplexClient service = new WCFSimplexClient("NetTcpBinding_IWCFSimplex1");
            service.Open();
            try {
                Console.WriteLine($"Service method Add(5,4) returns {service.Add(5, 4)}");
                Console.WriteLine($"Service method Concat(Hello, 1.65) returns {service.Concat("Hello", 1.65)}");
                A a1 = new A { s = "Hello", k = 5, f = 1.5f }, a2 = new A { s = "World", k = -1, f = -0.25f };
                A result = service.Sum(a1, a2);
                Console.WriteLine($"Service method Sum({{ s = {a1.s}, k = {a1.k}, f = {a1.f}}},{{ s = {a2.s}, k = {a2.k}, f = {a2.f}}}) returns {{ s = {result.s}, k = {result.k}, f = {result.f}}}");
            }
            catch (Exception ex) {
                Console.WriteLine($"Service unreachable: {ex.Message}!");
            }
            service.Close();
        }
    }
}
