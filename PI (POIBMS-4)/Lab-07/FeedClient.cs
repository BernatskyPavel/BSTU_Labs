﻿//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан программой.
//     Исполняемая версия:4.0.30319.42000
//
//     Изменения в этом файле могут привести к неправильной работе и будут потеряны в случае
//     повторной генерации кода.
// </auto-generated>
//------------------------------------------------------------------------------



[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
[System.ServiceModel.ServiceContractAttribute(ConfigurationName="IFeed1")]
public interface IFeed1
{
    
    [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IFeed1/CreateFeed", ReplyAction="http://tempuri.org/IFeed1/CreateFeedResponse")]
    System.ServiceModel.Syndication.SyndicationFeedFormatter CreateFeed();
    
    [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IFeed1/CreateFeed", ReplyAction="http://tempuri.org/IFeed1/CreateFeedResponse")]
    System.Threading.Tasks.Task<System.ServiceModel.Syndication.SyndicationFeedFormatter> CreateFeedAsync();
}

[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
public interface IFeed1Channel : IFeed1, System.ServiceModel.IClientChannel
{
}

[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
public partial class Feed1Client : System.ServiceModel.ClientBase<IFeed1>, IFeed1
{
    
    public Feed1Client()
    {
    }
    
    public Feed1Client(string endpointConfigurationName) : 
            base(endpointConfigurationName)
    {
    }
    
    public Feed1Client(string endpointConfigurationName, string remoteAddress) : 
            base(endpointConfigurationName, remoteAddress)
    {
    }
    
    public Feed1Client(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
            base(endpointConfigurationName, remoteAddress)
    {
    }
    
    public Feed1Client(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
            base(binding, remoteAddress)
    {
    }
    
    public System.ServiceModel.Syndication.SyndicationFeedFormatter CreateFeed()
    {
        return base.Channel.CreateFeed();
    }
    
    public System.Threading.Tasks.Task<System.ServiceModel.Syndication.SyndicationFeedFormatter> CreateFeedAsync()
    {
        return base.Channel.CreateFeedAsync();
    }
}
