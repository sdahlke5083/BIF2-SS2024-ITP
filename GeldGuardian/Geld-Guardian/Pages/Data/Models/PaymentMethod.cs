using Microsoft.EntityFrameworkCore;

namespace Geld_Guardian.Pages.Data.Models
{
    [PrimaryKey("PaymentId")]
    public class PaymentMethod
    {
        public int PaymentId { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

    }
}
