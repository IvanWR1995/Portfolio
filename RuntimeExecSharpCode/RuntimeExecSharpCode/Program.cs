using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Management.Automation;
using System.Collections.ObjectModel;
using System.Reflection;
namespace RuntimeExecSharpCode
{
    class Program
    {
        static string[] str = new string[1]{"Hi"};
        static void Main(string[] args)
        {
            string[] Code = new string[1]{"\"using System; public class ExecObj2{public  void Executer(ref object  o){o+=`\"Replace str`\";}}\""};
               
            
            ExecCSharpCode(Code[0]);
            Console.WriteLine((string)str[0]);
             Console.ReadLine();
        }
      /*  static void ExecPSCode()
        {

            using (PowerShell PowerShellInstance = PowerShell.Create())
            {
                PowerShellInstance.AddScript("get-process");

                Collection<PSObject> PSOutput = PowerShellInstance.Invoke();
                foreach (PSObject outputItem in PSOutput)
                {
                    if (outputItem != null)
                    {
                        System.Diagnostics.Process p = outputItem.BaseObject as System.Diagnostics.Process;
                        string str = p.StartInfo.WorkingDirectory;
                        Console.WriteLine("Name:{0} Threads Count:{1}", p.ProcessName, p.Threads.Count);

                    }
                }
            }
        }*/
        static void ExecCSharpCode(string code)
        {

            using (PowerShell PowerShellInstance = PowerShell.Create())
            {

                string script = String.Format(" Add-Type -TypeDefinition {0} -Language CSharp;  New-Object -TypeName ExecObj2", code);
                Console.WriteLine(script);
                PowerShellInstance.AddScript(script);
                Collection<PSObject> PSOutput = PowerShellInstance.Invoke();
                foreach (PSObject outputItem in PSOutput)
                {
                    if (outputItem != null)
                    {
                        Type type = outputItem.BaseObject.GetType();
                        object obj = Activator.CreateInstance(type);
                        MethodInfo method = type.GetMethod("Executer");
                        method.Invoke(obj,str);
                    }
                }
            }
        }
     
    }
}
