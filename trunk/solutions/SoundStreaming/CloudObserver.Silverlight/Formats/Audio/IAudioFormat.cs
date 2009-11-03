using System;

namespace CloudObserver.Formats.Audio
{
    /// <summary>
    /// Interface of a type which represents some class of audio format (e.g. PCM or MP3).
    /// Instances of such type represent a specific, parametrized format (e.g. 8kHz, 8bit, Stereo PCM).
    /// </summary>
    /// <remarks>\
    /// Format describes how the data is encoded (format type) and the encoding parameters (format properties).
    /// A specific format can contain information about format of sound from which
    /// the data was generated. E.g. MP3 format would be described by different structure (format type)
    /// but it could contain information about waveform from which the MP3 was encoded.
    /// </remarks>
    public interface IAudioFormat
    {
        string FormatClassName { get; }
        string Description { get; }
    }
}