using ProtoBuf;

namespace Transport.Protocol
{
    [ProtoContract]
    internal class OperationGetOperationsPublisherResponse : OperationResponse
    {
        [ProtoMember(1)]
        public string Adress { get; set; }
    }
}