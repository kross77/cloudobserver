using ProtoBuf;

namespace Transport.Protocol
{
    [ProtoContract]
    internal class OperationGetEventsPublisherResponse : OperationResponse
    {
        [ProtoMember(1)]
        public string Address { get; set; }
    }
}