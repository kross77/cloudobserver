using ProtoBuf;

namespace Transport.Protocol
{
    [ProtoContract]
    internal class OperationSetEventsPublisherRequest : OperationRequest<OperationResponse>
    {
        [ProtoMember(1)]
        public string Adress { get; set; }
        [ProtoMember(2)]
        public string Topic { get; set; }
    }
}