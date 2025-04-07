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

**Behavioral focus**: Ownership, Customer Obsession, Bias for Action, Learn and Be Curious

**Situation**:  
A major client evaluating Orkes required a Go SDK, which we didn’t have. Without it, we risked losing them.

**Task**:  
I volunteered to create the SDK from scratch, despite my limited experience in Go. The goal was to meet client needs and secure the deal.

**Action**:  
I studied existing SDKs and ramped up quickly in Go. I worked directly with the client, iterating based on feedback and ensuring compatibility with our platform.

**Result**:  
We successfully delivered the SDK on time. The client signed on, and the Go SDK became a foundation for future integrations.

## Orkes - Managing Multiple SDKs and Automation

**Behavioral focus**: Invent and Simplify, Insist on the Highest Standards, Deliver Results

**Situation**:  
We needed to support SDKs in multiple languages (Python, Go, JavaScript, C#) to address enterprise client needs.

**Task**:  
I led development of these SDKs and optimized them for high-throughput workflows. I also owned automation of testing and deployment.

**Action**:  
I added multiprocessing to the Python SDK to bypass GIL limits. I coordinated language-specific efforts while standardizing interfaces. Automated CI/CD pipelines reduced friction in releases.

**Result**:  
We scaled from 1 to 5 SDKs and enabled broader client adoption. Delivery speed increased and operational overhead dropped.

## Orkes - Resolving a Managerial Disagreement Over a Technical Decision

**Behavioral focus**: Have Backbone; Disagree and Commit, Dive Deep, Earn Trust

**Situation**:  
While designing the Python SDK, my manager and I disagreed over multithreading vs. multiprocessing.

**Task**:  
I needed to back my recommendation for multiprocessing with evidence and get alignment.

**Action**:  
I ran benchmarks and shared performance results. I clearly presented the implications of GIL and tradeoffs in each approach.

**Result**:  
We aligned on multiprocessing. Performance improved significantly, and the team was more confident in future technical discussions.

## Orkes - Improving SDK Documentation and Reducing Customer Complaints

**Behavioral focus**: Customer Obsession, Invent and Simplify, Deliver Results

**Situation**:  
We received consistent support complaints about confusing SDK onboarding and usage.

**Task**:  
I proposed overhauling documentation with better examples and side-by-side multi-language code snippets.

**Action**:  
I reused working test examples and worked with the tech writing team to improve clarity and flow.

**Result**:  
Support tickets dropped by 75%, onboarding time decreased, and customer sentiment improved.

## Amazon - Scaling Amazon FBA Invoice Services for Black Friday

**Behavioral focus**: Deliver Results, Think Big, Dive Deep, Ownership

**Situation**:  
FBA invoice services needed to scale for a 10x traffic spike during Black Friday.

**Task**:  
Ensure the system could withstand the load, prevent downtime, and dynamically scale.

**Action**:  
I led load testing efforts, identified bottlenecks, and implemented dynamic scaling strategies for infra efficiency.

**Result**:  
The system ran smoothly with 99.99% uptime and reduced infrastructure costs post-peak.

## Amazon - Implementing Load Testing in Service Pipelines

**Behavioral focus**: Bias for Action, Dive Deep, Ownership

**Situation**:  
We had a TPS generator tool but no working configuration, threatening our resilience score.

**Task**:  
Get the tool working, integrate it into the CI/CD pipeline, and enforce TPS thresholds.

**Action**:  
I experimented with configs, reached out to peers, and ultimately adapted a fix from another team’s workaround.

**Result**:  
The pipeline passed resilience benchmarks. The team gained confidence in performance and prevented underperforming builds from shipping.

## Amazon - Improving On-call Efficiency and Solving Resource-Related Issues

**Behavioral focus**: Ownership, Invent and Simplify, Are Right, A Lot

**Situation**:  
Our on-call rotation was noisy due to lack of monitoring and recurring resource issues (e.g., disk space failures).

**Task**:  
Improve alerting, clean up manual issues, and build long-term fixes for storage bugs.

**Action**:  
I implemented alarms, updated runbooks, and worked on infra upgrades. I later contributed a fix that deleted leftover invoice files.

**Result**:  
Reduced ticket volume, fewer outages, and a more maintainable and observable system.
