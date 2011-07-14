namespace CloudObserver
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
        OK
    }
}
