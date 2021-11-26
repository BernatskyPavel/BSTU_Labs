using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;
using System.ServiceModel.Web;

namespace Lab_07_Console
{
    class Program
    {
        static void Main(string[] args)
        {

            Simple.OData.Client.V3Adapter.Reference();
            WebServiceHost host = new WebServiceHost(typeof(Lab_07.NotesFeed));
            host.Open();
            Console.WriteLine("Host opened!\nPress any key to stop...");
            Console.Read();
            host.Close();
            Console.WriteLine("Host closed!");
        }
    }
}
