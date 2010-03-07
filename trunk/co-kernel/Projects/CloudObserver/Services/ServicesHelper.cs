using System;

namespace CloudObserver.Services
{
    /// <summary>
    /// Contains some static helper methods to work with services.
    /// </summary>
    public static class ServicesHelper
    {
        /// <summary>
        /// Returns a service contract type from a string representation of the service type.
        /// </summary>
        /// <param name="serviceType">String representation of the service type.</param>
        /// <exception cref="System.ArgumentException">Thrown when there is no service type with given string representation.</exception>
        /// <returns>Service contract type.</returns>
        public static Type GetServiceContract(string serviceType)
        {
            switch (serviceType)
            {
                default:
                    throw new ArgumentException("Invalid service type.");
            }
        }

        /// <summary>
        /// Creates an instance of a service by a string representation of the service type.
        /// </summary>
        /// <param name="serviceType">String representation of the service type.</param>
        /// <exception cref="System.ArgumentException">Thrown when there is no service type with given string representation.</exception>
        /// <returns>An instance of the service.</returns>
        public static Object CreateServiceInstance(string serviceType)
        {
            switch (serviceType)
            {
                default:
                    throw new ArgumentException("Invalid service type.");
            }
        }
    }
}