campaign_steps = {}
campaign_menu = {}

for i=1,10 do
  campaign_steps[#campaign_steps + 1] = function() RunImageStep(string.format("campaigns/terran/EstT%02d.txt", i)) end
  campaign_menu[#campaign_menu + 1] = #campaign_steps
  campaign_steps[#campaign_steps + 1] = CreateMapStep(string.format("campaigns/terran/%02d/scenario.smp", i))
end
