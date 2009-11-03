using System;
using System.Text;
using System.ServiceModel;
using System.Collections.Generic;

using CloudObserver.Formats;

namespace CloudObserver.Services.StreamingService
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    [CallbackBehavior(ConcurrencyMode = ConcurrencyMode.Multiple, UseSynchronizationContext = false)]
    public class StreamingService : IStreamingService
    {
        private Dictionary<IStreamingServiceCallback, DateTime> subscribers = new Dictionary<IStreamingServiceCallback, DateTime>();
        private List<IStreamingServiceCallback> timedOutSubscribers = new List<IStreamingServiceCallback>();
        private byte[] subscriptionResponse;

        public event EventHandler<DataTransferredEventArgs> DataTransfered;
        public event EventHandler<SubscribersChangedEventArgs> SubscribersChanged;

        public StreamingService()
        {
            subscriptionResponse = Encoding.UTF8.GetBytes(FormatIdentifiers.FormatNone);
            //{ 1, 0, 2, 0, 68, 172, 0, 0, 16, 177, 2, 0, 4, 0, 16, 0 } // 44100 Hz, 16 bit, Stereo WaveFormat
        }

        public void Send(byte[] data)
        {
            List<IStreamingServiceCallback> timedOutSubscribers = new List<IStreamingServiceCallback>();
            foreach (KeyValuePair<IStreamingServiceCallback, DateTime> subscriber in subscribers)
                if (subscriber.Value > DateTime.Now)
                    try
                    {
                        subscriber.Key.DataCallback(data);
                    }
                    catch (Exception)
                    {
                        timedOutSubscribers.Add(subscriber.Key);
                    }
                else
                    timedOutSubscribers.Add(subscriber.Key);
            foreach (IStreamingServiceCallback timedOutSubscriber in timedOutSubscribers)
                subscribers.Remove(timedOutSubscriber);
            DataTransfered.Invoke(this, new DataTransferredEventArgs(data.Length));
            if (timedOutSubscribers.Count > 0)
                SubscribersChanged.Invoke(this, new SubscribersChangedEventArgs(subscribers.Count));
            timedOutSubscribers.Clear();
        }

        public void SetSubscriptionResponse(byte[] response)
        {
            subscriptionResponse = response;
            foreach (IStreamingServiceCallback subscriber in subscribers.Keys)
                subscriber.SubscriptionResponse(subscriptionResponse);
        }

        public void Subscribe(TimeSpan timeout)
        {
            IStreamingServiceCallback subscriber = OperationContext.Current.GetCallbackChannel<IStreamingServiceCallback>();
            if (subscribers.ContainsKey(subscriber))
                subscribers[subscriber] = DateTime.Now.Add(timeout);
            else
            {
                subscribers.Add(subscriber, DateTime.Now.Add(timeout));
                subscriber.SubscriptionResponse(subscriptionResponse);
                SubscribersChanged.Invoke(this, new SubscribersChangedEventArgs(subscribers.Count));
            }
        }

        public void Unsubscribe()
        {
            IStreamingServiceCallback subscriber = OperationContext.Current.GetCallbackChannel<IStreamingServiceCallback>();
            if (subscribers.ContainsKey(subscriber))
            {
                subscribers.Remove(subscriber);
                SubscribersChanged.Invoke(this, new SubscribersChangedEventArgs(subscribers.Count));
            }
        }
    }
}