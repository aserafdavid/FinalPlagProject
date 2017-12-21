using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows;
using Caliburn.Micro;

namespace PlagiarismUI
{
    public class PlagiarismUIBootstrapper : BootstrapperBase
    {
        #region Consts

        private const string ModuleSearchPattern = "*.dll";

        #endregion

        #region Protected Methods

        /// <summary>
        /// Called by Caliburn Framework.
        /// Override to tell the framework where to find assemblies to inspect for views in Dynamic Modules,
        /// The Referenced dlls are covered by calling to base.
        /// </summary>
        /// <returns>
        /// A list of assemblies to inspect.
        /// </returns>
        protected override IEnumerable<Assembly> SelectAssemblies()
        {
            var runtimeDir = AppDomain.CurrentDomain.BaseDirectory;
            return Directory.GetFiles(runtimeDir, ModuleSearchPattern).Select(Assembly.LoadFrom).ToList();
        }
        
        protected override void OnStartup(object sender, StartupEventArgs e)
        {
            try
            {
                DisplayRootViewFor<MainShellViewModel>();
            }
            catch (Exception)
            {
                Application.Shutdown();
            }

            base.OnStartup(sender, e);
        }

        #endregion
    }
}