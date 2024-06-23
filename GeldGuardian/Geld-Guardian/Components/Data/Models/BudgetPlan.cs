using Microsoft.AspNetCore.Identity;

namespace Geld_Guardian.Components.Data.Models
{
    public class BudgetPlan
    {
        public int Id { get; set; }
        public int CategoryId { get; set; }
        public string UserId { get; set; }
        public decimal Amount { get; set; }

        // Navigation properties
        public virtual Categorie Category { get; set; }
        public virtual IdentityUser User { get; set; }

    }
}
