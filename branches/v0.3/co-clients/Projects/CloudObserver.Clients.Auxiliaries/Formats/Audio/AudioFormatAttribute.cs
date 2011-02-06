using System;

namespace CloudObserver.Clients.Auxiliaries.Formats.Audio
{
    /// <summary>
    /// Decorates a type which represents some audio format class (e.g. PCM or MP3).
    /// </summary>
    [AttributeUsage(AttributeTargets.Struct | AttributeTargets.Class, Inherited = false, AllowMultiple = false)]
    public sealed class AudioFormatAttribute : Attribute
    {
        public string Name { get; private set; }

        public AudioFormatAttribute(string name)
        {
            this.Name = name;
        }
    }
}
