## Summary

- [Summary](#summary)
- [Suggested Questions to Prepare For](#suggested-questions-to-prepare-for)
- [Orkes - Creating an SDK to Win a Major Client](#orkes---creating-an-sdk-to-win-a-major-client)
- [Orkes - Managing Multiple SDKs and Automation](#orkes---managing-multiple-sdks-and-automation)
- [Orkes - Resolving a Managerial Disagreement Over a Technical Decision](#orkes---resolving-a-managerial-disagreement-over-a-technical-decision)
- [Orkes - Improving SDK Documentation and Reducing Customer Complaints](#orkes---improving-sdk-documentation-and-reducing-customer-complaints)
- [Amazon - Scaling Amazon FBA Invoice Services for Black Friday](#amazon---scaling-amazon-fba-invoice-services-for-black-friday)
- [Amazon - Implementing Load Testing in Service Pipelines](#amazon---implementing-load-testing-in-service-pipelines)
- [Amazon - Improving On-call Efficiency and Solving Resource-Related Issues](#amazon---improving-on-call-efficiency-and-solving-resource-related-issues)
- [Beyond - Leadership in High-Frequency Trading Web Application Development](#beyond---leadership-in-high-frequency-trading-web-application-development)

## Suggested Questions to Prepare For

1. **Ownership and Delivery**  
   - Tell me about a time you took ownership of a project and delivered results.

2. **Influencing Decisions**  
   - Describe a situation where you had to convince a team or management of a particular course of action.  
   - Give me an example of when you took an unpopular stance in a meeting with peers and your leader and you were the outlier. What was it, and what did you do?

3. **Goal Setting and Achievement**  
   - Give an example of a goal you set and achieved, and how you went about it.  
   - Tell me about a goal that you set that took a long time to achieve or that you are still working towards.

4. **Learning New Technologies Quickly**  
   - Explain a time when you had to learn a new technology or tool quickly. How did you handle it?  
   - Tell me about a time when you realized you needed to have a deeper level of subject matter expertise to do your job well.

5. **Handling Conflict**  
   - Describe a time you had to handle a conflict in a team. What steps did you take?

6. **Responding to Critical Feedback**  
   - Tell me about a time you received critical feedback. How did you respond?

7. **Adapting to Change**  
   - Share an example of when you needed to adapt to a significant change in a project or strategy.

8. **Technical Optimization**  
   - Give an example of a time you reduced technical debt or optimized a system.

9. **Problem Solving and Impact**  
   - Describe a challenging problem you solved that had a meaningful impact on your team or company.  
   - Tell me about a time when you linked two or more problems together and identified an underlying issue. Were you able to find a solution?

10. **Seeking Diverse Perspectives**  
   - Tell me about a time where you sought out perspectives other than your own to make a product, service, or project better.

11. **Quick Analysis and Response**  
   - Tell me about a time when you had to analyze facts quickly, define key issues, and respond immediately to a situation. What was the outcome?

12. **Using Customer Feedback for Improvement**  
   - Give me an example of a time you used customer feedback to drive improvement or innovation. What was the situation and what action did you take?

13. **Balancing Short-term vs. Long-term Goals**  
   - Tell me about a time you made a hard decision to sacrifice short-term gain for a longer-term goal.

14. **Driving Vision Adoption**  
   - How do you drive adoption for your vision or ideas?  
   - How do you know how well your idea or vision has been adopted by other teams or partners? Give a specific example highlighting one of your ideas.

15. **Striving for Excellence**  
   - Tell me about a time you wouldn’t compromise on achieving a great outcome when others felt something was good enough. What was the situation?


## Orkes - Creating an SDK to Win a Major Client

- **Situation**:
  A major client was evaluating Orkes but required an SDK written in Go, which we did not have at the time. Without it, we were at risk of losing the client.

- **Task**:
  I volunteered to take on the task of creating a Go SDK from scratch, despite my limited experience with the language. The goal was to meet the client's needs and secure the deal.

- **Action**:
  I quickly learned the intricacies of Go, referring to the existing SDKs as references. I communicated regularly with the client to ensure the SDK met their expectations, iterating on feedback and making adjustments. I also integrated the new SDK with our existing platform to ensure compatibility and smooth functionality.

- **Result**:
  The Go SDK was successfully delivered on time, meeting all the client's requirements. This not only helped win the client but also positioned Orkes to support a broader range of customers who required SDKs in Go. Client satisfaction increased, and the SDK was reused for other customer integrations.


## Orkes - Managing Multiple SDKs and Automation

- **Situation**:
  Orkes needed SDKs for several programming languages to meet diverse customer demands. We already had a Java SDK, but we needed to develop Python, Go, JavaScript, and C# versions. There was also a need to improve performance through parallel processing.

- **Task**:
  I was tasked with managing the development of these SDKs and ensuring they supported parallel processing for higher throughput. I also needed to automate the CI/CD pipeline to streamline testing and deployment.

- **Action**:
  I took the lead in developing the Python SDK, incorporating multiprocessing after careful testing to overcome Python’s GIL limitations. I also worked closely with the team to scale the SDK offerings from one to five languages, ensuring they all supported efficient parallel processing. Additionally, I set up automation for the CI/CD process, significantly reducing manual intervention.

- **Result**:
  The SDK offerings grew from just one in Java to five in various languages. These SDKs enabled the company to support more workflows and improve throughput. The automated CI/CD process increased deployment speed and reliability, allowing for faster delivery to clients.


## Orkes - Resolving a Managerial Disagreement Over a Technical Decision

- **Situation**:
  While working on the Python SDK, there was a disagreement between me and my manager over whether to use multithreading or multiprocessing. The manager favored multithreading for its simplicity, but I was concerned about Python’s GIL, which would limit performance.

- **Task**:
  I needed to convince my manager and the team that multiprocessing was the better option for our use case, ensuring we delivered a performant SDK.

- **Action**:
  I conducted detailed tests comparing multithreading and multiprocessing, gathering data to back up my recommendation. I presented the findings to my manager and the team, explaining the long-term benefits of adopting multiprocessing. After several discussions and review, the team agreed to switch to multiprocessing.

- **Result**:
  The final decision to use multiprocessing improved the SDK’s performance, allowing it to handle more parallel tasks and reducing bottlenecks. This led to a more efficient system overall and a successful project delivery.


## Orkes - Improving SDK Documentation and Reducing Customer Complaints

- **Situation**:
  After we developed several SDKs, we noticed that customers were struggling with onboarding due to unclear documentation, which led to a high volume of complaints.

- **Task**:
  I proposed improving the SDK documentation by adding clearer examples and live code snippets in the wiki. The goal was to make the SDKs more user-friendly and reduce customer complaints.

- **Action**:
  I added real code snippets from our tests to the documentation and suggested displaying examples in multiple languages side by side for better understanding. I worked closely with the technical writing team to ensure consistency and clarity across all SDK documentation.

- **Result**:
  The improved documentation led to a 75% reduction in customer complaints. Customers were able to onboard more easily, and the SDKs became much more accessible, leading to higher satisfaction and fewer support requests.

## Amazon - Scaling Amazon FBA Invoice Services for Black Friday

- **Situation**:
  During the lead-up to Black Friday, the Amazon FBA invoice service needed to be scaled to handle the huge influx of requests. Without proper preparation, the system could fail under the high load.

- **Task**:
  I was responsible for load testing and capacity planning to ensure the system could handle 10x the usual traffic and quickly downscale afterward.

- **Action**:
  I worked with the team to implement load testing strategies and forecast system capacity. We tested the system under simulated Black Friday conditions, identifying bottlenecks and optimizing them. Additionally, I set up a system for dynamic scaling to handle peak traffic and efficiently downscale after the rush.

- **Result**:
  The FBA invoice service handled the Black Friday traffic without any issues, maintaining 99.99% uptime. The ability to dynamically scale up and down saved costs during non-peak times and increased the team’s confidence in the system’s reliability.


## Amazon - Implementing Load Testing in Service Pipelines

- **Situation**:
  Our team at Amazon was required to meet certain resilience scores, which included adding automated load testing to every service pipeline. However, the tool we were supposed to use, a TPS (Transactions Per Second) generator, was not as plug-and-play as expected. No one in the team could configure it properly, and we were at risk of missing the resilience score target, which would have attracted unwanted attention.

- **Task**:
  I took the initiative to lead the effort in integrating the load testing tool. The goal was to set up a new step in the pipeline that would run a batch of requests, measure the maximum TPS a host could handle, and set minimum TPS requirements to pass the pipeline, much like an integration test.

- **Action**:
  I communicated with my manager to set expectations and reached out to various team members, including neighboring teams, for advice. Despite their attempts, no one had a working solution. I methodically experimented with configurations, iterating daily and testing different settings. After days of trial and error, I found a similar service from AWS that had faced the same issue and successfully fixed it with a small code snippet. I adapted that solution and applied it to our service.

- **Result**:
  Once the load testing tool was correctly integrated, we transitioned from being in the red for resilience scoring to green. Every service in our team’s pipeline now had automated load testing, allowing us to monitor the performance in terms of TPS and latency, and enforce minimum requirements for each deployment. This also reduced the risk for our team and increased confidence in our service performance.

## Amazon - Improving On-call Efficiency and Solving Resource-Related Issues

- **Situation**:  
  When I joined Amazon, I was onboarded into the on-call rotation quite early. Our team handled many manual tasks that were the result of edge cases not accounted for in the code. Additionally, one of our systems had limited monitoring, and it wasn’t well optimized to handle resource usage, leading to frequent on-call issues. A recurring problem involved requests failing due to storage issues caused by auxiliary invoice files not being properly deleted after use, which led to storage space being exhausted.

- **Task**:  
  My task was twofold: to improve the monitoring of this system and reduce the number of manual interventions required for recurring on-call issues. I also aimed to resolve the storage issue to prevent request failures and rejected requests due to insufficient space.

- **Action**:  
  I took the initiative to create alarms for resource usage monitoring, particularly for the system that wasn’t previously well-monitored. This included adding alerts for storage and CPU usage. Additionally, I analyzed the recurring issues and noticed that many tickets were related to the same storage problem, caused by auxiliary invoice files not being deleted after use. I updated the runbook with the solution to this problem, making it easier for team members to quickly resolve it in the future. Finally, I worked with the team to implement a temporary fix by upgrading the host machine capacity, which gave us time to find a long-term solution.

- **Result**:  
  The addition of resource monitoring alarms allowed us to proactively detect and prevent resource issues before they escalated into larger problems. The runbook update made the recurring storage issue easier to resolve, leading to faster ticket resolution and reduced manual intervention. As a result, the team was able to handle on-call issues more efficiently, and the system experienced fewer outages and rejected requests due to storage constraints.


## Beyond - Leadership in High-Frequency Trading Web Application Development
- **Focus**: Leadership in spearheading a project, managing client certifications, and technical excellence.
- **Details to Include**:
  - How you led the development of a high-frequency trading web app.
  - Managing communication and certifications with external clients (e.g., B3).
  - Technical challenges and solutions implemented.
