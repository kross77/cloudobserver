namespace CloudObserverLite
{
    public enum ParserState
    {
        METHOD,
        URL,
        URLPARAM,
        URLVALUE,
        VERSION,
        HEADERKEY,
        HEADERVALUE,
        BODY,
        STREAM,
        OK
    }
}
