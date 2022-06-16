campaign_steps = {}
campaign_menu = {}

campaign_steps[#campaign_steps + 1] = function() RunImageStep(string.format("campaigns/zerg/EstZ0t.txt", i)) end
campaign_menu[#campaign_menu + 1] = #campaign_steps
campaign_steps[#campaign_steps + 1] = CreateMapStep(string.format("campaigns/zerg/tutorial/scenario.smp", i))

for i=1,10 do
  campaign_steps[#campaign_steps + 1] = function() RunImageStep(string.format("campaigns/zerg/EstZ%02d.txt", i)) end
  campaign_menu[#campaign_menu + 1] = #campaign_steps
  campaign_steps[#campaign_steps + 1] = CreateMapStep(string.format("campaigns/zerg/%02d/scenario.smp", i))
end
