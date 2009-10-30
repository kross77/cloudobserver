using System;

namespace CloudObserver.Silverlight.Formats.Audio
{
    /// <summary>
    /// Base class simplifying implementation of IAudioFormat.
    /// </summary>
    public abstract class AudioFormatBase : IAudioFormat
    {
        public string FormatClassName
        {
            get { return GetSourceFormatClassName(GetType()); }
        }

        public abstract string Description { get; }

        public static string GetSourceFormatClassName(Type audioFormatType)
        {
            AudioFormatAttribute audioFormatAttribute = (AudioFormatAttribute)Attribute.GetCustomAttribute(audioFormatType, typeof(AudioFormatAttribute));
            if (audioFormatAttribute == null)
                return audioFormatType.ToString();

            return audioFormatAttribute.Name;
        }
    }
}