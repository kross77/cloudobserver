using ProtoBuf;

namespace Transport.Protocol
{
    [ProtoContract]
    internal class OperationGetEventsPublisherResponse : OperationResponse
    {
        [ProtoMember(1)]
        public string Adress { get; set; }
    }
}