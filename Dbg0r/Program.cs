using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Threading;
using System.Runtime.InteropServices;
using MinHook;

namespace Dbg0r {
	unsafe static class Program {
		[DllImport("vcmssm_new", CallingConvention = CallingConvention.Cdecl)]
		static extern void do_drugs();


		[STAThread]
		static void Main(string[] args) {
			Console.Write("Doing drugs ... ");
			do_drugs();
			RunProgram();
		}

		static void RunProgram() {
			Assembly VCMEditor = Assembly.Load("VCM Editor");
			MethodInfo Main = VCMEditor.EntryPoint;
			Main.Invoke(null, new[] { new string[] { } });
		}
	}
}