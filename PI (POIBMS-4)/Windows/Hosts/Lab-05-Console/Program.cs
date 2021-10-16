using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_05;
using System.ServiceModel;

namespace Lab_05_Console {
    class Program {
        static void Main(string[] args)
        {
            ServiceHost host = new ServiceHost(typeof(Lab_05.WCFSimplex));
            host.Open();
            Console.WriteLine("Host opened!\nPress any key to stop...");
            Console.Read();
            host.Close();
            Console.WriteLine("Host closed!");
        }
    }
}
